#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>
#include <mutex>
#include <memory>

class User;

class Room {
private:
	std::vector<User*> usersInRoom;
	std::mutex roomMutex;

public:
	Room() = default;
	~Room() = default;

	void addUser(User* user);
	void removeUser(User* user);
	void deliverMessage(std::string msg, User* sender);
	std::vector<User*> getUsers();
};

#endif

