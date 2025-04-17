#include "../headers/logger.h"


std::mutex Logger::logMutex;
std::chrono::system_clock::time_point Logger::startTime; 