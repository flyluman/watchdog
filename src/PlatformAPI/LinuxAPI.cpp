#include "PlatformAPI/LinuxAPI.h"
#include "utils/Logger.h"
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <cstdlib>

bool LinuxAPI::isProcessRunning(const std::string& processName) {
    std::string command = "pgrep " + processName + " > /dev/null 2>&1";
    int result = system(command.c_str());
    return (result == 0);
}

void LinuxAPI::startProcess(const std::string& processName, const std::string& parameters) {
    std::string command = processName + " " + parameters + " &";
    system(command.c_str());
    Logger::log("Started process " + processName + " with parameters: " + parameters);
}

void LinuxAPI::stopProcess(const std::string& processName) {
    std::string command = "pkill " + processName;
    system(command.c_str());
    Logger::log("Stopped process " + processName);
}
