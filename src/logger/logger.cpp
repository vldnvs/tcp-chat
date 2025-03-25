#include "../../headers/logger.h"

// Определение статических членов класса Logger
std::mutex Logger::logMutex;
std::chrono::system_clock::time_point Logger::startTime; 