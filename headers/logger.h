#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <chrono>
#include <mutex>

class Logger {
private:
        static std::mutex logMutex;
        static std::chrono::system_clock::time_point startTime;

public:
        static void init() {
                startTime = std::chrono::system_clock::now();
        }

        static void log(const std::string& message, const std::string& component = "System") {
                std::lock_guard<std::mutex> lock(logMutex);
                auto now = std::chrono::system_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
                std::cout << "[" << duration.count() << "ms] [" << component << "] " << message << std::endl;
        }

        static void error(const std::string& message, const std::string& component = "System") {
                std::lock_guard<std::mutex> lock(logMutex);
                auto now = std::chrono::system_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
                std::cerr << "[" << duration.count() << "ms] [" << component << "] ERROR: " << message << std::endl;
        }
};

#endif 