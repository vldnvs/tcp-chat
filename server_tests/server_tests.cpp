#define BOOST_TEST_MODULE ServerTests
#include <boost/test/unit_test.hpp>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

using boost::asio::ip::tcp;
using namespace std::chrono_literals;

// Test client helper class
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
        boost::asio::write(socket_, boost::asio::buffer(message + "\r\n"));
    }

    std::string receive() {
        boost::asio::streambuf buffer;
        boost::asio::read_until(socket_, buffer, '\n');
        std::istream is(&buffer);
        std::string message;
        std::getline(is, message);
        // Remove \r if present
        if (!message.empty() && message.back() == '\r') {
            message.pop_back();
        }
        return message;
    }

    void close() {
        socket_.close();
    }

private:
    boost::asio::io_context io_context_;
    tcp::socket socket_;
};

// Test fixture for server tests
struct ServerTestFixture {
    ServerTestFixture() {
        // Give the server time to start
        std::this_thread::sleep_for(100ms);
    }
};

BOOST_FIXTURE_TEST_SUITE(ServerTests, ServerTestFixture)

// Test 1: Basic connection and nickname setting
BOOST_AUTO_TEST_CASE(test_basic_connection) {
    TestClient client("127.0.0.1", 13);
    
    // Should receive welcome message
    std::string welcome = client.receive();
    BOOST_CHECK_EQUAL(welcome, "Welcome to the chat server!");
    
    // Should receive nickname prompt
    std::string prompt = client.receive();
    BOOST_CHECK_EQUAL(prompt, "Please enter your nickname: ");
    
    // Send nickname
    client.send("test_user");
    
    client.close();
}

// Test 2: Message exchange between clients
BOOST_AUTO_TEST_CASE(test_message_exchange) {
    TestClient client1("127.0.0.1", 13);
    TestClient client2("127.0.0.1", 13);
    
    // Handle welcome messages and prompts
    client1.receive(); // Welcome
    client1.receive(); // Nickname prompt
    client2.receive(); // Welcome
    client2.receive(); // Nickname prompt
    
    // Set nicknames
    client1.send("user1");
    client2.send("user2");
    
    // Send message from user1
    client1.send("hello");
    
    // user2 should receive the message
    std::string message = client2.receive();
    BOOST_CHECK_EQUAL(message, "user1: hello");
    
    client1.close();
    client2.close();
}

// Test 3: Client disconnection
BOOST_AUTO_TEST_CASE(test_client_disconnection) {
    TestClient client1("127.0.0.1", 13);
    TestClient client2("127.0.0.1", 13);
    
    // Handle welcome messages and prompts
    client1.receive(); // Welcome
    client1.receive(); // Nickname prompt
    client2.receive(); // Welcome
    client2.receive(); // Nickname prompt
    
    // Set nicknames
    client1.send("user1");
    client2.send("user2");
    
    // Close first client
    client1.close();
    
    // Give server time to process disconnection
    std::this_thread::sleep_for(100ms);
    
    client2.close();
}

// Test 4: Invalid nickname (empty)
BOOST_AUTO_TEST_CASE(test_invalid_nickname) {
    TestClient client("127.0.0.1", 13);
    
    // Handle welcome messages and prompts
    client.receive(); // Welcome
    client.receive(); // Nickname prompt
    
    // Send empty nickname
    client.send("");
    
    // Should still be able to send another nickname
    client.send("valid_user");
    
    client.close();
}

// Test 5: Multiple messages in sequence
BOOST_AUTO_TEST_CASE(test_multiple_messages) {
    TestClient client1("127.0.0.1", 13);
    TestClient client2("127.0.0.1", 13);
    
    // Handle welcome messages and prompts
    client1.receive(); // Welcome
    client1.receive(); // Nickname prompt
    client2.receive(); // Welcome
    client2.receive(); // Nickname prompt
    
    // Set nicknames
    client1.send("user1");
    client2.send("user2");
    
    // Send multiple messages
    std::vector<std::string> messages = {
        "hello",
        "how are you",
        "goodbye"
    };
    
    for (const auto& msg : messages) {
        client1.send(msg);
        std::string received = client2.receive();
        BOOST_CHECK_EQUAL(received, "user1: " + msg);
    }
    
    client1.close();
    client2.close();
}

BOOST_AUTO_TEST_SUITE_END() 