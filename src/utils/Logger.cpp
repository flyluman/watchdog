#include "utils/Logger.h"
#include <fstream>
#include <ctime>
#include <cstring>

std::string Logger::logFilePath;

void Logger::initialize(const std::string& logFilePath) {
    Logger::logFilePath = logFilePath;
}

void Logger::log(const std::string& message) {
    std::ofstream logFile(logFilePath, std::ios_base::app);
    if (logFile.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);
        dt[strlen(dt) - 1] = '\0';  // Remove newline
        logFile << "[" << dt << "] " << message << std::endl;
    }
}
