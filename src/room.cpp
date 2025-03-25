#include "room.h"
#include "user.h"
#include "logger.h"
#include <algorithm>

void Room::addUser(User* user) {
	if (!user) {
		Logger::error("Attempt to add null user", "Room");
		return;
	}
	
	std::lock_guard<std::mutex> lock(roomMutex);
	if (std::find(usersInRoom.begin(), usersInRoom.end(), user) == usersInRoom.end()) {
		usersInRoom.push_back(user);
		Logger::log("User added to room. Total users: " + std::to_string(usersInRoom.size()), "Room");
	} else {
		Logger::log("Attempt to add duplicate user", "Room");
	}
}

void Room::removeUser(User* user) {
	if (!user) {
		Logger::error("Attempt to remove null user", "Room");
		return;
	}
	
	std::lock_guard<std::mutex> lock(roomMutex);
	auto it = std::find(usersInRoom.begin(), usersInRoom.end(), user);
	if (it != usersInRoom.end()) {
		usersInRoom.erase(it);
		Logger::log("User removed from room. Total users: " + std::to_string(usersInRoom.size()), "Room");
	} else {
		Logger::log("Attempt to remove non-existent user", "Room");
	}
}

void Room::deliverMessage(std::string msg, User* sender) {
	if (!sender) {
		Logger::error("Attempt to deliver message from null sender", "Room");
		return;
	}
	
	std::lock_guard<std::mutex> lock(roomMutex);
	int deliveredCount = 0;
	for (User* user : usersInRoom) {
		if (user && user != sender) {
			user->queueMsg(msg);
			deliveredCount++;
		}
	}
	Logger::log("Message delivered to " + std::to_string(deliveredCount) + " users", "Room");
}

std::vector<User*> Room::getUsers() {
	std::lock_guard<std::mutex> lock(roomMutex);
	Logger::log("Getting users list. Total users: " + std::to_string(usersInRoom.size()), "Room");
	return usersInRoom;
}