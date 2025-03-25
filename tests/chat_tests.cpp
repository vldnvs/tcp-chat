#define BOOST_TEST_MODULE ChatAppTests
#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>

#include "../headers/user.h"
#include "../headers/server.h"
#include "../headers/room.h"

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

using boost::asio::ip::tcp;

class TestFixture {
public:
    boost::asio::io_service io_service;
    std::unique_ptr<Room> room;
    std::unique_ptr<Server> server;
    
    TestFixture() : room(std::make_unique<Room>()) {
        server = std::make_unique<Server>(io_service);
    }
    
    ~TestFixture() {
        server->stop();
    }
};

BOOST_FIXTURE_TEST_SUITE(ChatServerTests, TestFixture)

BOOST_AUTO_TEST_CASE(ServerCreationTest) {
    BOOST_CHECK(server->running());
}

BOOST_AUTO_TEST_CASE(RoomOperationsTest) {
    BOOST_CHECK_EQUAL(room->getUsers().size(), 0);
    
    User* user1 = User::getPointer(io_service, room.get());
    BOOST_CHECK_EQUAL(room->getUsers().size(), 1);
    
    User* user2 = User::getPointer(io_service, room.get());
    BOOST_CHECK_EQUAL(room->getUsers().size(), 2);
    
    room->removeUser(user1);
    BOOST_CHECK_EQUAL(room->getUsers().size(), 1);
    
    room->removeUser(user2);
    BOOST_CHECK_EQUAL(room->getUsers().size(), 0);
    
    delete user1;
    delete user2;
}

BOOST_AUTO_TEST_CASE(UserPropertiesTest) {
    User* user = User::getPointer(io_service, room.get());
    
    BOOST_CHECK_EQUAL(user->nameSet, false);
    BOOST_CHECK_EQUAL(user->waitingForPong, false);
    
    user->name = "TestUser";
    user->nameSet = true;
    
    BOOST_CHECK_EQUAL(user->name, "TestUser");
    BOOST_CHECK_EQUAL(user->nameSet, true);
    
    delete user;
}

BOOST_AUTO_TEST_CASE(MessageQueueTest) {
    std::shared_ptr<User> user(User::getPointer(io_service, room.get()));
    
    std::string testMessage = "Test message";
    user->queueMsg(testMessage);
    
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(ServerStopTest) {
    BOOST_CHECK(server->running());
    server->stop();
    BOOST_CHECK(!server->running());
    
    server = std::make_unique<Server>(io_service);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(UserConnectionTests)

BOOST_AUTO_TEST_CASE(UserConnectionTimingTest) {
    boost::asio::io_service io;
    std::unique_ptr<Room> testRoom = std::make_unique<Room>();
    
    User* user = User::getPointer(io, testRoom.get());
    auto currentTime = user->uptime;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    BOOST_CHECK(user->uptime == currentTime);
    
    delete user;
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(IntegrationTests)

BOOST_AUTO_TEST_CASE(ServerRoomIntegrationTest) {
    boost::asio::io_service io;
    std::unique_ptr<Room> testRoom = std::make_unique<Room>();
    std::unique_ptr<Server> testServer = std::make_unique<Server>(io);
    
    BOOST_CHECK(testServer->running());
    
    std::vector<User*> users;
    const int numUsers = 5;
    
    for (int i = 0; i < numUsers; i++) {
        users.push_back(User::getPointer(io, testRoom.get()));
    }
    
    BOOST_CHECK_EQUAL(testRoom->getUsers().size(), numUsers);
    
    for (auto* user : users) {
        testRoom->removeUser(user);
        delete user;
    }
    
    BOOST_CHECK_EQUAL(testRoom->getUsers().size(), 0);
    
    testServer->stop();
    BOOST_CHECK(!testServer->running());
}

BOOST_AUTO_TEST_SUITE_END() 