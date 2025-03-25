#include "server.h"

Server::Server(io_serv& io) : accept(io, tcp::endpoint(tcp::v4(), 13)), 
                             server_time(clock_::now()), 
                             io_service(io) {
        room = new Room();
        setupSignalHandlers();
        startThreadPool();
        monitoringThread = std::thread(&Server::monitor, this);
        waitForConnection();
}

Server::~Server() {
        stop();
        
        // Ждем завершения всех потоков
        for (auto& thread : thread_pool) {
                if (thread.joinable()) {
                        thread.join();
                }
        }
        
        if (monitoringThread.joinable()) {
                monitoringThread.join();
        }
        
        delete room;
}

void Server::setupSignalHandlers() {
        boost::asio::signal_set signals(io_service, SIGINT, SIGTERM);
        signals.async_wait([this](const boost::system::error_code& ec, int signal) {
                if (!ec) {
                        std::cout << "Received signal " << signal << ". Shutting down..." << std::endl;
                        stop();
                }
        });
}

void Server::startThreadPool() {
        auto work = std::make_shared<boost::asio::io_service::work>(io_service);
        
        for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
                thread_pool.emplace_back([this, work]() {
                        io_service.run();
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
        
        for (User* user : room->getUsers()) {
                if (user->nameSet) {
                        boost::asio::post(io_service, [user]() {
                                auto now = clock_::now();
                                auto uptime = std::chrono::duration<double>(now - user->uptime).count();
                                
                                if (uptime > 100) {
                                        user->disconnect();
                                        return;
                                }
                                
                                user->waitingForPong = true;
                                user->lastPingTime = now;
                                user->queueMsg("PING\r\n");
                                
                                auto timer = std::make_shared<boost::asio::deadline_timer>(
                                        io_service,
                                        boost::posix_time::seconds(20)
                                );
                                
                                timer->async_wait([user, timer](const boost::system::error_code& ec) {
                                        if (!ec && user->waitingForPong) {
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
                                        
                                        if (line == "/show_uptime") {
                                                std::cout << "Server uptime: " 
                                                        << std::chrono::duration<double>(clock_::now() - this->server_time).count() 
                                                        << " seconds" << std::endl;
                                                std::cout << ">> ";
                                                asyncReadLine(buffer);
                                        }
                                        else if (line == "/shutdown") {
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
        
        User* ptr = User::getPointer(io_service, room);
        accept.async_accept(ptr->getSocket(), boost::bind(&Server::acceptHandler, this, boost::asio::placeholders::error, ptr));
}

void Server::acceptHandler(const boost::system::error_code& ec, User* ptr) {
        if (!is_running) {
                ptr->disconnect();
                return;
        }
        
        ptr->queueMsg("Welcome to the chat server!\r\n");
        ptr->queueMsg("Please enter your nickname: ");
        ptr->readMsg();
        waitForConnection();
}

// health check от сервера для клиентов
// использовать thread pool  
// доделать асинхронность
// тесты