#ifndef LINUX_API_H
#define LINUX_API_H

#include "PlatformAPI/PlatformAPI.h"

class LinuxAPI : public PlatformAPI {
public:
    bool isProcessRunning(const std::string& processName) override;
    void startProcess(const std::string& processName, const std::string& parameters) override;
    void stopProcess(const std::string& processName) override;
};

#endif
