#include "server.h"

void pauseOneSecond() noexcept {
	std::chrono::time_point<clock_> pause = clock_::now();
	while (clock_::now() - pause < std::chrono::duration<double>(1)) {};
}

Server::Server(io_serv& io) :accept(io, tcp::endpoint(tcp::v4(), 13)), server_time(clock_::now()) {
	waitForConnection();
	room = new Room();
	monitoringThread = std::thread(&Server::monitor, this);
}

void Server::monitor() {
	int count = AUTOMATIC_SHUTDOWN_IN_SECS;
	std::string input;
	while (true) {
		std::cout << ">> ";
		std::getline(std::cin, input);
		if (input == "show_time")std::cout<<std::chrono::duration<double>(clock_::now() - this->server_time ).count()<< std::endl;
	}
	//	(clock_::now() - this->server_time < std::chrono::duration<double>(AUTOMATIC_SHUTDOWN_IN_SECS)) {

	//}
	for (User* ptr : room->getUsers()) {
		ptr->disconnect();
	}
}
void Server::waitForConnection() {
	User* ptr = User::getPointer(accept.get_io_service(), room);
	accept.async_accept(ptr->getSocket(), boost::bind(&Server::acceptHandler, this, boost::asio::placeholders::error, ptr));
}

void Server::acceptHandler(const boost::system::error_code& ec, User* ptr) {
	ptr->queueMsg("To enter the chat please insert your nickname: ");
	ptr->readMsg();


	waitForConnection();
}