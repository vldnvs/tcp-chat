#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/function.hpp>
#include "user.h"
#include <chrono>
#include <thread>
#include <vector>
#include <functional>

using namespace boost::placeholders;

typedef boost::asio::io_context io_serv;
using boost::asio::ip::tcp;

class Server {
	Room* room;
	tcp::acceptor accept;
	boost::asio::streambuf commandLineBuffer;
	io_serv& io_service;
	std::chrono::time_point<clock_> server_time;
	std::vector<std::thread> thread_pool;
	std::thread monitoringThread;
	bool is_running = true;
	const int AUTOMATIC_SHUTDOWN_IN_SECS = 20;
	const int THREAD_POOL_SIZE = 4;

public:
	Server(io_serv& io, const tcp::endpoint& endpoint);
	~Server();
	void stop() { 
		is_running = false; 
		io_service.stop(); 
	}
	bool running() const { return is_running; }
	void setupSignalHandlers();

private:
	void waitForConnection();
	void acceptHandler(const boost::system::error_code& ec, User* ptr);
	void handle_write(const boost::system::error_code& /*error*/,
		size_t) {

	};
	void monitor();
	void startThreadPool();
	void healthCheck();
};





#endif 