#include "user.h"
#include "logger.h"


void User::queueMsg(std::string msg) {
	if (!socket_.is_open()) {
		Logger::error("Attempt to queue message to closed socket for user: " + (nameSet ? name : "unnamed"), "User");
		return;
	}

	if (msg.length() < 2 || msg.substr(msg.length() - 2) != "\r\n") {
		msg += "\r\n";
	}
	
	writeBuffer.push_back(msg);
	Logger::log("Message queued for user: " + (nameSet ? name : "unnamed") + 
				" (Queue size: " + std::to_string(writeBuffer.size()) + ")", "User");
	
	if (writeBuffer.size() == 1) {
		boost::asio::async_write(
			socket_,
			boost::asio::buffer(writeBuffer.front().data(), writeBuffer.front().length()),
			boost::bind(
				&User::handle_write,
				this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)
		);
	}
}

 
void User::readMsg() {
	if (!socket_.is_open()) {
		Logger::error("Attempt to read from closed socket", "User");
		return;
	}

	Logger::log("Starting async read for user: " + (nameSet ? name : "unnamed"), "User");
	boost::asio::async_read_until(
		socket_, 
		readBuffer, 
		'\n', 
		boost::bind(
			&User::handle_read, 
			this, 
			boost::asio::placeholders::error, 
			boost::asio::placeholders::bytes_transferred
		)
	);
}


void User::handle_write(const boost::system::error_code& error, size_t)
{
	if (!error && socket_.is_open())
	{
		if (!writeBuffer.empty()) {
			writeBuffer.pop_front();
			Logger::log("Message sent to user: " + (nameSet ? name : "unnamed") + 
						" (Remaining queue size: " + std::to_string(writeBuffer.size()) + ")", "User");
			
			if (!writeBuffer.empty())
			{
				Logger::log("Processing next message in queue for user: " + (nameSet ? name : "unnamed"), "User");
				boost::asio::async_write(
					socket_,
					boost::asio::buffer(writeBuffer.front().data(),
						writeBuffer.front().length()),
					boost::bind(
						&User::handle_write,
						this,
						boost::asio::placeholders::error, 
						boost::asio::placeholders::bytes_transferred
					)
				);
			}
		} else {
			Logger::log("Write buffer is empty for user: " + (nameSet ? name : "unnamed"), "User");
		}
	}
	else
	{
		Logger::error("Write error for user: " + (nameSet ? name : "unnamed") + 
					(error ? " - " + error.message() : "") + 
					" (Queue size: " + std::to_string(writeBuffer.size()) + ")", "User");
		chatRoom->removeUser(this);
	}
}

void User::handle_read(const boost::system::error_code& error, size_t)
{
	if (!error && socket_.is_open())
	{
		std::istream is(&readBuffer);
		std::string line;
		std::getline(is, line);
		
		line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
		line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
		
		if (line.empty()) {
			Logger::log("Empty message received from user: " + (nameSet ? name : "unnamed"), "User");
			readMsg();
			return;
		}
		
		Logger::log("Message received from user: " + (nameSet ? name : "unnamed") + " - " + line, "User");
		
		if (line == "PONG") {
			waitingForPong = false;
			uptime = clock_::now();
			Logger::log("PONG received from user: " + name, "User");
			readMsg();
			return;
		}

		// Process the message
		handleMessage(line);
		
		// Continue reading
		readMsg();
	}
	else {
		Logger::error("Read error for user: " + (nameSet ? name : "unnamed") + 
					(error ? " - " + error.message() : ""), "User");
		chatRoom->removeUser(this);
	}
}

void User::handleMessage(const std::string& message) {
	if (!nameSet) {
		// Handle nickname setting
		name = message;
		nameSet = true;
		Logger::log("User set name: " + name, "User");
		chatRoom->addUser(this);
		return;
	}
	
	// Handle commands
	if (message == "LIST") {
		chatRoom->broadcastUserList();
	}
	else if (message == "HISTORY") {
		chatRoom->sendHistory(this);
	}
	else if (message.substr(0, 4) == "MSG ") {
		// Handle chat message
		std::string chatMsg = name + ": " + message.substr(4);  // Remove "MSG " prefix
		chatRoom->deliverMessage(chatMsg, this);
	}
	else if (message.substr(0, 5) == "JOIN ") {
		// Handle join message (already handled in nickname setting)
		return;
	}
	else if (message.substr(0, 6) == "LEAVE ") {
		// Handle leave message
		std::string leaveMsg = name + " left the chat";
		chatRoom->deliverMessage(leaveMsg, this);
		chatRoom->removeUser(this);
		disconnect();
	}
}


 