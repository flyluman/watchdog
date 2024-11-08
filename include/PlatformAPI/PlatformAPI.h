#ifndef PLATFORM_API_H
#define PLATFORM_API_H

#include <string>

class PlatformAPI {
public:
    virtual ~PlatformAPI() = default;
    virtual bool isProcessRunning(const std::string& processName) = 0;
    virtual void startProcess(const std::string& processName, const std::string& parameters) = 0;
    virtual void stopProcess(const std::string& processName) = 0;
};

#endif
