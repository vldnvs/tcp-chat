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
	std::vector<std::string> chat_history;
	std::mutex history_mutex;
	static const size_t MAX_HISTORY_SIZE = 100;

public:
	Room() = default;
	~Room() = default;

	void addUser(User* user);
	void removeUser(User* user);
	void deliverMessage(std::string msg, User* sender);
	std::vector<User*> getUsers();
	void broadcast(const std::string& message, User* sender = nullptr);
	void addToHistory(const std::string& message);
	std::string getHistory();
	
	// New methods for better room management
	void broadcastUserList();
	void sendHistory(User* user);
	void broadcastJoinMessage(User* user);
	void broadcastLeaveMessage(User* user);
	std::string getUserList();
};

#endif

