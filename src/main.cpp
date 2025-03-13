#include <boost/asio.hpp>
#include "server.h"


int main() {
	boost::asio::io_service io;
	Server server(io);
	io.run();
}