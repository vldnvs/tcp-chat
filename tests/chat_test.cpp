#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include "../src/server.h"
#include "../src/user.h"
#include "../src/room.h"
#include "../src/logger.h"

class ChatTest : public ::testing::Test {
protected:
    void SetUp() override {
        Logger::init();
        io_service = new boost::asio::io_service();
        server = new Server(*io_service);
    }

    void TearDown() override {
        delete server;
        delete io_service;
    }

    boost::asio::io_service* io_service;
    Server* server;
};

TEST_F(ChatTest, BasicChatFunctionality) {
    // Создаем тестового пользователя
    User* testUser = User::getPointer(*io_service, server->getRoom());
    
    // Проверяем, что пользователь успешно добавлен в комнату
    ASSERT_TRUE(server->getRoom()->getUsers().size() > 0);
    
    // Проверяем, что пользователь получил приветственное сообщение
    testUser->readMsg();
    io_service->run_one();
    
    // Проверяем, что пользователь может отправить сообщение
    std::string testMessage = "Hello, chat!";
    testUser->queueMsg(testMessage);
    io_service->run_one();
    
    // Проверяем, что сообщение было доставлено другим пользователям
    auto users = server->getRoom()->getUsers();
    bool messageDelivered = false;
    for (auto user : users) {
        if (user != testUser) {
            messageDelivered = true;
            break;
        }
    }
    
    ASSERT_TRUE(messageDelivered);
}

TEST_F(ChatTest, HealthCheckAndDisconnect) {
    // Создаем тестового пользователя
    User* testUser = User::getPointer(*io_service, server->getRoom());
    
    // Устанавливаем имя пользователя для теста
    testUser->name = "TestUser";
    testUser->nameSet = true;
    
    // Проверяем, что пользователь добавлен в комнату
    ASSERT_TRUE(server->getRoom()->getUsers().size() > 0);
    
    // Имитируем получение PING от сервера
    testUser->waitingForPong = true;
    testUser->lastPingTime = std::chrono::steady_clock::now();
    
    // Отправляем PONG
    testUser->queueMsg("PONG\r\n");
    io_service->run_one();
    
    // Проверяем, что флаг waitingForPong сброшен
    ASSERT_FALSE(testUser->waitingForPong);
    
    // Имитируем таймаут
    testUser->waitingForPong = true;
    testUser->lastPingTime = std::chrono::steady_clock::now() - std::chrono::seconds(30);
    
    // Запускаем health check
    server->healthCheck();
    io_service->run_one();
    
    // Проверяем, что пользователь отключен
    ASSERT_FALSE(testUser->getSocket().is_open());
    ASSERT_TRUE(server->getRoom()->getUsers().empty());
}

TEST_F(ChatTest, MultipleUsersAndRoomManagement) {
    // Создаем трех тестовых пользователей
    User* user1 = User::getPointer(*io_service, server->getRoom());
    User* user2 = User::getPointer(*io_service, server->getRoom());
    User* user3 = User::getPointer(*io_service, server->getRoom());
    
    // Устанавливаем имена пользователей
    user1->name = "User1";
    user1->nameSet = true;
    user2->name = "User2";
    user2->nameSet = true;
    user3->name = "User3";
    user3->nameSet = true;
    
    // Проверяем, что все пользователи добавлены в комнату
    ASSERT_EQ(server->getRoom()->getUsers().size(), 3);
    
    // Отправляем сообщение от первого пользователя
    std::string message = "Hello everyone!";
    user1->queueMsg(message);
    io_service->run_one();
    
    // Проверяем, что сообщение получено другими пользователями
    bool user2Received = false;
    bool user3Received = false;
    
    for (auto user : server->getRoom()->getUsers()) {
        if (user != user1) {
            if (user == user2) user2Received = true;
            if (user == user3) user3Received = true;
        }
    }
    
    ASSERT_TRUE(user2Received);
    ASSERT_TRUE(user3Received);
    
    // Отключаем одного пользователя
    user2->disconnect();
    io_service->run_one();
    
    // Проверяем, что пользователь удален из комнаты
    ASSERT_EQ(server->getRoom()->getUsers().size(), 2);
    
    // Проверяем, что отключенный пользователь не получает сообщения
    user1->queueMsg("New message");
    io_service->run_one();
    
    // Проверяем, что сообщение получено только активным пользователем
    bool messageDeliveredToActiveUser = false;
    for (auto user : server->getRoom()->getUsers()) {
        if (user != user1 && user->getSocket().is_open()) {
            messageDeliveredToActiveUser = true;
        }
    }
    
    ASSERT_TRUE(messageDeliveredToActiveUser);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 