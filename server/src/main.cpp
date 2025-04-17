#include <boost/asio.hpp>
#include "server.h"
#include <thread>
#include <chrono>
#include <csignal>
#include <iostream>

int main() {
	try {
		boost::asio::io_service io;
		Server server(io);
		
		io.run();
		
		return 0;
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return 1;
	}
}