#ifndef ROOM_H
#define ROOM_H

class User;
#include <vector>


static std::vector<User*> usersInRoom;

class Room {

public:
	void addUser(User* user);
	void removeUser(User* user);
	void deliverMessage(std::string msg, User* sender);
	std::vector<User*> getUsers();


};

#endif

