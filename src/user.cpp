#include <user.h>


void User::queueMsg(std::string msg) {
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
	if (!error )
	{
		std::istream is(&readBuffer);
		std::string line;
		std::getline(is, line);
		line=line.substr(0, line.length() - 1);
		std::cout << line << std::endl;
		if (!nameSet) {
			name = line;
			nameSet = true;
			readMsg();
			return;
		}

		chatRoom->deliverMessage(line+"\r\n", this);

		readMsg();

	}
	else {
		chatRoom->removeUser(this);
	}
}


 