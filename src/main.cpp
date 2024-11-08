#include "WatchdogManager.h"
#include "utils/Logger.h"
#include <csignal>
#include <memory>
#include <iostream>

#define LOG_FILE "watchlog.log"
#define CONFIG_PATH "config/watchdog_config.yaml"

std::unique_ptr<WatchdogManager> watchdog;

void handleSigint(int signal) {
    Logger::log("SIGINT received. Exiting Watchdog...");
    if (watchdog) {
        watchdog->stop();
    }
    Logger::log("Watchdog exited gracefully...");
    std::cout << std::endl << "Watchdog exited gracefully..." << std::endl;
    exit(signal);
}

int main() {
    signal(SIGINT, handleSigint);

    Logger::initialize(LOG_FILE);
    Logger::log("Starting Watchdog. Press CTRL+C to exit...");
    std::cout << "Starting Watchdog. Press CTRL+C to exit..." << std::endl;

    watchdog = std::make_unique<WatchdogManager>(CONFIG_PATH);
    watchdog->start();

    Logger::log("Watchdog stopped.");
    return 0;
}
