#define BOOST_TEST_MODULE ServerTests
#include <boost/test/unit_test.hpp>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

using boost::asio::ip::tcp;
using namespace std::chrono_literals;

// Вспомогательный класс для тестового клиента
class TestClient {
public:
    TestClient(const std::string& host, unsigned short port)
        : io_context_()
        , socket_(io_context_)
    {
        tcp::resolver resolver(io_context_);
        boost::asio::connect(socket_, resolver.resolve(host, std::to_string(port)));
    }

    void send(const std::string& message) {
        boost::asio::write(socket_, boost::asio::buffer(message + "\n"));
    }

    std::string receive() {
        boost::asio::streambuf buffer;
        boost::asio::read_until(socket_, buffer, '\n');
        std::istream is(&buffer);
        std::string message;
        std::getline(is, message);
        return message;
    }

    void close() {
        socket_.close();
    }

private:
    boost::asio::io_context io_context_;
    tcp::socket socket_;
};

// Тест 1: Проверка подключения клиента
BOOST_AUTO_TEST_CASE(test_client_connection) {
    // Создаем тестового клиента
    TestClient client("127.0.0.1", 12345);
    
    // Отправляем сообщение о подключении
    client.send("JOIN test_user");
    
    // Получаем ответ от сервера
    std::string response = client.receive();
    
    // Проверяем, что сервер подтвердил подключение
    BOOST_CHECK_EQUAL(response, "SERVER: test_user joined the chat");
    
    client.close();
}

// Тест 2: Проверка отправки сообщения
BOOST_AUTO_TEST_CASE(test_message_sending) {
    // Создаем двух тестовых клиентов
    TestClient client1("127.0.0.1", 12345);
    TestClient client2("127.0.0.1", 12345);
    
    // Подключаем обоих клиентов
    client1.send("JOIN user1");
    client1.receive(); // Пропускаем сообщение о подключении
    
    client2.send("JOIN user2");
    client2.receive(); // Пропускаем сообщение о подключении
    
    // Отправляем сообщение от первого клиента
    client1.send("MSG user1: Hello, user2!");
    
    // Проверяем, что второй клиент получил сообщение
    std::string message = client2.receive();
    BOOST_CHECK_EQUAL(message, "MSG user1: Hello, user2!");
    
    client1.close();
    client2.close();
}

// Тест 3: Проверка отключения клиента
BOOST_AUTO_TEST_CASE(test_client_disconnection) {
    // Создаем двух тестовых клиентов
    TestClient client1("127.0.0.1", 12345);
    TestClient client2("127.0.0.1", 12345);
    
    // Подключаем обоих клиентов
    client1.send("JOIN user1");
    client1.receive(); // Пропускаем сообщение о подключении
    
    client2.send("JOIN user2");
    client2.receive(); // Пропускаем сообщение о подключении
    
    // Отключаем первого клиента
    client1.close();
    
    // Даем серверу время на обработку отключения
    std::this_thread::sleep_for(100ms);
    
    // Проверяем, что второй клиент получил уведомление об отключении
    std::string message = client2.receive();
    BOOST_CHECK_EQUAL(message, "SERVER: user1 left the chat");
    
    client2.close();
} 