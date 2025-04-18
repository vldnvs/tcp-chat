#ifndef USER_H
#define USER_H


#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <deque>
#include "room.h"
#include <chrono>


using boost::asio::ip::tcp;
typedef std::chrono::high_resolution_clock clock_;

class User {
	tcp::socket socket_;
	std::deque<std::string> writeBuffer;
	boost::asio::streambuf readBuffer;
	Room* chatRoom;
public:
	bool nameSet = false;
	std::chrono::time_point<clock_> uptime;
	std::string name;
	bool waitingForPong = false;
	std::chrono::time_point<clock_> lastPingTime;

public:

	static User* getPointer(boost::asio::io_context& io, Room* room) { 
		return new User(io, room); 
	}
	void queueMsg(std::string msg);
	void readMsg();

	User(boost::asio::io_context& io, Room* room) 
		: socket_(io)
		, chatRoom(room)
		, uptime(clock_::now()) 
	{ }

	void handle_write(const boost::system::error_code&, size_t);
	void handle_read(const boost::system::error_code&, size_t);
	tcp::socket& getSocket() {
		return socket_;
	}

	void disconnect() { 
		boost::system::error_code ec; 
		socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec); 
		socket_.close(ec); 
	}

	std::string getName() const { return name; }
	void handleMessage(const std::string& message);
	Room* getRoom() const { return chatRoom; }

};


#endif // !USER_H
