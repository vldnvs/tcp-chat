#include "room.h"
#include "user.h"


extern std::vector<User*> usersInRoom;

void Room::addUser(User* user) {

	usersInRoom.push_back(user);
}

void Room::removeUser(User* user) {
	std::cout << user->name << " has been removed" << std::endl;
	usersInRoom.erase(std::find(usersInRoom.begin(), usersInRoom.end(), user));
}

void Room::deliverMessage(std::string msg, User* sender) {
	for (User* recipient : usersInRoom) {
		if (recipient != sender && recipient->nameSet) {
			recipient->queueMsg(sender->name + ": " + msg);
		}
	}
}

std::vector < User*>  Room::getUsers() {
	return  usersInRoom;
}