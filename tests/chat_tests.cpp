#define BOOST_TEST_MODULE ChatTests
#include <boost/test/unit_test.hpp>
#include <boost/asio.hpp>
#include "../src/server.h"
#include "../src/user.h"
#include "../src/room.h"
#include "../src/logger.h"

struct ChatTestFixture {
    ChatTestFixture() {
        Logger::init();
        io_service = new boost::asio::io_service();
        server = new Server(*io_service);
    }

    ~ChatTestFixture() {
        delete server;
        delete io_service;
    }

    boost::asio::io_service* io_service;
    Server* server;
};

BOOST_FIXTURE_TEST_SUITE(ChatTests, ChatTestFixture)

BOOST_AUTO_TEST_CASE(BasicChatFunctionality) {
    User* testUser = User::getPointer(*io_service, server->getRoom());
    
    
    BOOST_CHECK(server->getRoom()->getUsers().size() > 0);
    
    testUser->readMsg();
    io_service->run_one();
    
    std::string testMessage = "Hello, chat!";
    testUser->queueMsg(testMessage);
    io_service->run_one();
    
    auto users = server->getRoom()->getUsers();
    bool messageDelivered = false;
    for (auto user : users) {
        if (user != testUser) {
            messageDelivered = true;
            break;
        }
    }
    
    BOOST_CHECK(messageDelivered);
}

BOOST_AUTO_TEST_CASE(HealthCheckAndDisconnect) {
    User* testUser = User::getPointer(*io_service, server->getRoom());
    
    testUser->name = "TestUser";
    testUser->nameSet = true;
    
    BOOST_CHECK(server->getRoom()->getUsers().size() > 0);
    
    testUser->waitingForPong = true;
    testUser->lastPingTime = std::chrono::steady_clock::now();
    
    testUser->queueMsg("PONG\r\n");
    io_service->run_one();
    
    BOOST_CHECK(!testUser->waitingForPong);
    
    testUser->waitingForPong = true;
    testUser->lastPingTime = std::chrono::steady_clock::now() - std::chrono::seconds(30);
    
    server->healthCheck();
    io_service->run_one();
    
    BOOST_CHECK(!testUser->getSocket().is_open());
    BOOST_CHECK(server->getRoom()->getUsers().empty());
}

BOOST_AUTO_TEST_CASE(MultipleUsersAndRoomManagement) {
    User* user1 = User::getPointer(*io_service, server->getRoom());
    User* user2 = User::getPointer(*io_service, server->getRoom());
    User* user3 = User::getPointer(*io_service, server->getRoom());
    
    user1->name = "User1";
    user1->nameSet = true;
    user2->name = "User2";
    user2->nameSet = true;
    user3->name = "User3";
    user3->nameSet = true;
    
    BOOST_CHECK_EQUAL(server->getRoom()->getUsers().size(), 3);
    
    std::string message = "Hello everyone!";
    user1->queueMsg(message);
    io_service->run_one();
    
    bool user2Received = false;
    bool user3Received = false;
    
    for (auto user : server->getRoom()->getUsers()) {
        if (user != user1) {
            if (user == user2) user2Received = true;
            if (user == user3) user3Received = true;
        }
    }
    
    BOOST_CHECK(user2Received);
    BOOST_CHECK(user3Received);
    
    user2->disconnect();
    io_service->run_one();
    
    BOOST_CHECK_EQUAL(server->getRoom()->getUsers().size(), 2);
    
    user1->queueMsg("New message");
    io_service->run_one();
    
    bool messageDeliveredToActiveUser = false;
    for (auto user : server->getRoom()->getUsers()) {
        if (user != user1 && user->getSocket().is_open()) {
            messageDeliveredToActiveUser = true;
        }
    }
    
    BOOST_CHECK(messageDeliveredToActiveUser);
}

BOOST_AUTO_TEST_SUITE_END() 