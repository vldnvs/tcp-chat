#include <boost/asio.hpp>
#include "../headers/server.h"
#include "../headers/logger.h"
#include <thread>
#include <chrono>
#include <csignal>
#include <iostream>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
	try {
		boost::asio::io_context io;
		tcp::endpoint endpoint(tcp::v4(), 12345); // Listen on port 12345
		Server server(io, endpoint);
		
		io.run();
		
		return 0;
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
		return 1;
	}
}