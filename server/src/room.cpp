#include "room.h"
#include "user.h"
#include "logger.h"
#include <algorithm>
#include <sstream>

void Room::addUser(User* user) {
	if (!user) {
		Logger::error("Attempt to add null user", "Room");
		return;
	}
	
	std::lock_guard<std::mutex> lock(roomMutex);
	if (std::find(usersInRoom.begin(), usersInRoom.end(), user) == usersInRoom.end()) {
		usersInRoom.push_back(user);
		Logger::log("User added to room. Total users: " + std::to_string(usersInRoom.size()), "Room");
		
		// Send current user list to the new user
		user->queueMsg("USERS " + getUserList() + "\r\n");
		
		// Send chat history to the new user
		sendHistory(user);
		
		// Broadcast join message to all users
		std::string joinMsg = user->getName() + " joined the chat";
		deliverMessage(joinMsg, user);
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
		
		// Update user list for all remaining users
		broadcastUserList();
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
	
	// Add message to history
	addToHistory(msg);
	
	// Deliver to all users except sender
	int deliveredCount = 0;
	for (User* user : usersInRoom) {
		if (user && user != sender && user->getSocket().is_open()) {
			user->queueMsg(msg + "\r\n");
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

void Room::broadcastUserList() {
	std::string userList = getUserList();
	std::lock_guard<std::mutex> lock(roomMutex);
	for (User* user : usersInRoom) {
		if (user && user->getSocket().is_open()) {
			user->queueMsg("USERS " + userList + "\r\n");
		}
	}
}

void Room::sendHistory(User* user) {
	if (!user) return;
	
	std::lock_guard<std::mutex> lock(history_mutex);
	std::stringstream history;
	history << "HISTORY ";
	
	for (const auto& msg : chat_history) {
		history << msg << "|";
	}
	
	user->queueMsg(history.str() + "\r\n");
}

std::string Room::getUserList() {
	std::lock_guard<std::mutex> lock(roomMutex);
	std::stringstream list;
	
	for (size_t i = 0; i < usersInRoom.size(); ++i) {
		if (usersInRoom[i] && usersInRoom[i]->getName() != "") {
			list << usersInRoom[i]->getName();
			if (i < usersInRoom.size() - 1) {
				list << ",";
			}
		}
	}
	
	return list.str();
}

void Room::addToHistory(const std::string& message) {
	std::lock_guard<std::mutex> lock(history_mutex);
	chat_history.push_back(message);
	// Keep only last MAX_HISTORY_SIZE messages to prevent memory issues
	if (chat_history.size() > MAX_HISTORY_SIZE) {
		chat_history.erase(chat_history.begin());
	}
}

std::string Room::getHistory() {
	std::lock_guard<std::mutex> lock(history_mutex);
	std::string history;
	for (const auto& msg : chat_history) {
		history += msg + "|";
	}
	return history;
}

void Room::broadcast(const std::string& message, User* sender) {
	std::lock_guard<std::mutex> lock(roomMutex);
	for (auto user : usersInRoom) {
		if (user && user != sender && user->getSocket().is_open()) {
			user->queueMsg(message + "\r\n");
		}
	}
}

void Room::broadcastJoinMessage(User* user) {
	if (!user) return;
	std::string joinMsg = user->getName() + " joined the chat";
	deliverMessage(joinMsg, user);
}

void Room::broadcastLeaveMessage(User* user) {
	if (!user) return;
	std::string leaveMsg = user->getName() + " left the chat";
	deliverMessage(leaveMsg, user);
}