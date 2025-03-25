#include "user.h"


void User::queueMsg(std::string msg) {
		// Убеждаемся, что сообщение заканчивается на \r\n
		if (msg.length() < 2 || msg.substr(msg.length() - 2) != "\r\n") {
			msg += "\r\n";
		}
		
		writeBuffer.push_back(msg);
		boost::asio::async_write
		(
			socket_,
			boost::asio::buffer(writeBuffer.front().data(), writeBuffer.front().length()),
			boost::bind
			(
				&User::handle_write,
				this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)
		);
}

 
void User::readMsg() {
	boost::asio::async_read_until(socket_, readBuffer, '\n', boost::bind(&User::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}


void User::handle_write(const boost::system::error_code& error, size_t)
{
	if (!error)
	{
		writeBuffer.pop_front();
		if (!writeBuffer.empty())
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(writeBuffer.front().data(),
					writeBuffer.front().length()),
				boost::bind(&User::handle_write,this,
					boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
	}
	else
	{
		chatRoom->removeUser(this);
	}
}

void User::handle_read(const boost::system::error_code& error, size_t)
{
	if (!error)
	{
		std::istream is(&readBuffer);
		std::string line;
		std::getline(is, line);
		
		// Удаляем все символы конца строки и пробелы
		line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
		line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		
		if (line.empty()) {
			readMsg();
			return;
		}
		
		std::cout << "Received: " << line << std::endl;
		
		if (!nameSet) {
			name = line;
			nameSet = true;
			readMsg();
			return;
		}

		// Обработка PONG сообщения
		if (line == "PONG") {
			waitingForPong = false;
			uptime = clock_::now();
			readMsg();
			return;
		}

		boost::asio::post(socket_.get_executor(), [this, line]() {
			chatRoom->deliverMessage(line + "\r\n", this);
		});

		readMsg();
	}
	else {
		chatRoom->removeUser(this);
	}
}


 