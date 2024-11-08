#include "WatchdogManager.h"
#include "utils/Logger.h"
#include "PlatformAPI/LinuxAPI.h"
#include "PlatformAPI/WindowsAPI.h"
#include <thread>
#include <chrono>

WatchdogManager::WatchdogManager(const std::string config_path) : running(true) {
    #ifdef __linux__
        platform = std::make_unique<LinuxAPI>();
    #else
        platform = std::make_unique<WindowsAPI>();
    #endif
    
    configLoader.loadConfig(config_path);
}

void WatchdogManager::start() {
    Logger::log("Initializing Watchdog Manager.");
    configLoader.startWatching();

    while (running) {
        monitorProcesses();
        configLoader.reloadConfigIfNeeded();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void WatchdogManager::stop() {
    running = false;
    auto processes = configLoader.getMonitoredProcesses();
    for (const auto& process : processes) {
        platform->stopProcess(process);
    }
    Logger::log("Watchdog Manager stopped.");
}

void WatchdogManager::monitorProcesses() {
    auto processes = configLoader.getMonitoredProcesses();
    for (const auto& process : processes) {
        if (!platform->isProcessRunning(process)) {
            Logger::log("Process " + process + " is not running. Starting it.");
            platform->startProcess(configLoader.getProcessCommand(process), configLoader.getProcessParameters(process));
        }
    }
}
