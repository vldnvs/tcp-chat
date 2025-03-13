#include "server.h"

Server::Server(io_serv& io) :accept(io, tcp::endpoint(tcp::v4(), 13)), server_time(clock_::now()) {
        waitForConnection();
        room = new Room();
        monitoringThread = std::thread(&Server::monitor, this);
}

void Server::monitor() {
        // int count = AUTOMATIC_SHUTDOWN_IN_SECS; ToDo: запилить автоматический шатдаун 
        std::string input;
        while (true) {
                std::cout << ">> ";
                std::getline(std::cin, input);
                if (input == "/show_uptime"){
					std::cout << "Server uptime: " 
                      << std::chrono::duration<double>(clock_::now() - this->server_time).count() 
                      << " seconds" << std::endl;
				}
				else if (input == "/shutdown"){
					break;
				}
        }
        for (User* ptr : room->getUsers()) {
                ptr->disconnect();
        }
		return;
}

void Server::waitForConnection() {
        User* ptr = User::getPointer(static_cast<boost::asio::io_context&>(accept.get_executor().context()), room);
        accept.async_accept(ptr->getSocket(), boost::bind(&Server::acceptHandler, this, boost::asio::placeholders::error, ptr));
}

void Server::acceptHandler(const boost::system::error_code& ec, User* ptr) {
        ptr->queueMsg("Hi! What`s your nickname?: ");
        ptr->readMsg();


        waitForConnection();
}