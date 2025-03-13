#ifndef SERVER_H
#define SERVER_H


#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "user.h"
#include <chrono>
#include <thread>


typedef boost::asio::io_service io_serv;
using boost::asio::ip::tcp;

class Server {
	tcp::acceptor accept;
	Room* room;
	std::chrono::time_point<clock_> server_time;
	std::thread monitoringThread;
	const int AUTOMATIC_SHUTDOWN_IN_SECS = 20;
	boost::asio::streambuf commandLineBuffer;

public:

	Server(io_serv& io);

private:
	void waitForConnection();
	void acceptHandler(const boost::system::error_code& ec, User* ptr);
	void handle_write(const boost::system::error_code&,
		size_t

	};
	void monitor();

};





#endif 