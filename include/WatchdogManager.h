#ifndef WATCHDOG_MANAGER_H
#define WATCHDOG_MANAGER_H

#include <string>
#include <memory>
#include "ConfigLoader.h"
#include "PlatformAPI/PlatformAPI.h"

class WatchdogManager {
public:
    WatchdogManager(const std::string config_path);
    void start();
    void stop();

private:
    ConfigLoader configLoader;
    std::unique_ptr<PlatformAPI> platform;
    bool running;

    void monitorProcesses();
};

#endif
