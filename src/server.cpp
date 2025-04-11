#include "server.h"
#include "logger.h"

Server::Server(io_serv& io) : accept(io, tcp::endpoint(tcp::v4(), 13)), 
                             server_time(clock_::now()), 
                             io_service(io) {
        Logger::init();
        Logger::log("Server starting...", "Server");
        room = new Room();
        setupSignalHandlers();
        startThreadPool();
        monitoringThread = std::thread(&Server::monitor, this);
        waitForConnection();
        Logger::log("Server started successfully", "Server");
}

Server::~Server() {
        Logger::log("Server shutting down...", "Server");
        stop();
        
        for (auto& thread : thread_pool) {
                if (thread.joinable()) {
                        thread.join();
                }
        }
        
        if (monitoringThread.joinable()) {
                monitoringThread.join();
        }
        
        delete room;
        Logger::log("Server shutdown complete", "Server");
}

void Server::setupSignalHandlers() {
        Logger::log("Setting up signal handlers", "Server");
        boost::asio::signal_set signals(io_service, SIGINT, SIGTERM);
        signals.async_wait([this](const boost::system::error_code& ec, int signal) {
                if (!ec) {
                        Logger::log("Received signal " + std::to_string(signal), "Server");
                        stop();
                }
        });
}

void Server::startThreadPool() {
        Logger::log("Starting thread pool with " + std::to_string(THREAD_POOL_SIZE) + " threads", "Server");
        auto work = std::make_shared<boost::asio::io_service::work>(io_service);
        
        for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
                thread_pool.emplace_back([this, work]() {
                        Logger::log("Thread started", "Server");
                        io_service.run();
                        Logger::log("Thread finished", "Server");
                });
        }
        
        boost::asio::post(io_service, [this]() {
                healthCheck();
        });
}

// Тайминги:
// 100 секунд - Интервал проверки клиентов
// 20 секунд - Время на ответ клиента
void Server::healthCheck() {
        if (!is_running) return;
        
        Logger::log("Starting health check", "Server");
        for (User* user : room->getUsers()) {
                if (user->nameSet) {
                        boost::asio::post(io_service, [this, user]() {
                                auto now = clock_::now();
                                auto uptime = std::chrono::duration<double>(now - user->uptime).count();
                                
                                if (uptime > 100) {
                                        Logger::log("User " + user->name + " timeout", "Server");
                                        user->disconnect();
                                        return;
                                }
                                
                                user->waitingForPong = true;
                                user->lastPingTime = now;
                                user->queueMsg("PING\r\n");
                                
                                auto timer = std::make_shared<boost::asio::deadline_timer>(
                                        this->io_service,
                                        boost::posix_time::seconds(20)
                                );
                                
                                timer->async_wait([user, timer](const boost::system::error_code& ec) {
                                        if (!ec && user->waitingForPong) {
                                                Logger::log("User " + user->name + " failed to respond to PING", "Server");
                                                user->disconnect();
                                        }
                                });
                        });
                }
        }
        
        if (is_running) {
                auto timer = std::make_shared<boost::asio::deadline_timer>(io_service, boost::posix_time::seconds(120));
                timer->async_wait([this, timer](const boost::system::error_code& ec) {
                        if (!ec && is_running) {
                                healthCheck();
                        }
                });
        }
}

void Server::monitor() {
        Logger::log("Starting command monitor", "Server");
        boost::asio::posix::stream_descriptor input(io_service, ::dup(STDIN_FILENO));
        
        std::function<void(boost::asio::streambuf&)> asyncReadLine;
        asyncReadLine = [this, &input, &asyncReadLine](boost::asio::streambuf& buffer) {
                boost::asio::async_read_until(
                        input, 
                        buffer, 
                        '\n',
                        [this, &input, &buffer, &asyncReadLine](const boost::system::error_code& ec, std::size_t size) {
                                if (!ec && is_running) {
                                        std::istream is(&buffer);
                                        std::string line;
                                        std::getline(is, line);
                                        
                                        Logger::log("Command received: " + line, "Server");
                                        
                                        if (line == "/show_uptime") {
                                                auto uptime = std::chrono::duration<double>(clock_::now() - this->server_time).count();
                                                std::cout << "Server uptime: " << uptime << " seconds" << std::endl;
                                                std::cout << ">> ";
                                                asyncReadLine(buffer);
                                        }
                                        else if (line == "/shutdown") {
                                                Logger::log("Shutdown command received", "Server");
                                                stop();
                                                for (User* ptr : room->getUsers()) {
                                                        ptr->disconnect();
                                                }
                                                input.close();
                                                return;
                                        }
                                        else {
                                                std::cout << "Unknown command. Available commands are: /show_uptime, /shutdown" << std::endl;
                                                std::cout << ">> ";
                                                asyncReadLine(buffer);
                                        }
                                }
                        }
                );
        };
        
        std::cout << ">> ";
        asyncReadLine(commandLineBuffer);
        
        io_service.run();
}

void Server::waitForConnection() {
        if (!is_running) return;
        
        Logger::log("Waiting for new connection", "Server");
        User* ptr = User::getPointer(io_service, room);
        accept.async_accept(ptr->getSocket(), 
                [this, ptr](const boost::system::error_code& ec) {
                        if (!ec) {
                                Logger::log("New connection accepted", "Server");
                                try {
                                        acceptHandler(ec, ptr);
                                } catch (const std::exception& e) {
                                        Logger::error("Error in acceptHandler: " + std::string(e.what()), "Server");
                                        ptr->disconnect();
                                        delete ptr;
                                }
                        } else {
                                Logger::error("Accept error: " + ec.message(), "Server");
                                delete ptr;
                        }
                });
}

void Server::acceptHandler(const boost::system::error_code& ec, User* ptr) {
        if (!is_running) {
                Logger::log("Server not running, rejecting connection", "Server");
                ptr->disconnect();
                delete ptr;
                return;
        }
        
        try {
                if (!ptr->getSocket().is_open()) {
                        throw std::runtime_error("Socket is not open");
                }
                
                Logger::log("Sending welcome message to new user", "Server");
                ptr->queueMsg("Welcome to the chat server!\r\n");
                ptr->queueMsg("Please enter your nickname: ");
                
                boost::asio::post(io_service, [ptr]() {
                        ptr->readMsg();
                });
                
                boost::asio::post(io_service, [this]() {
                        waitForConnection();
                });
        } catch (const std::exception& e) {
                Logger::error("Error in acceptHandler: " + std::string(e.what()), "Server");
                ptr->disconnect();
                delete ptr;
                throw;
        }
}