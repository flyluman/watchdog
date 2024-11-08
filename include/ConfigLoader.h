#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class ConfigLoader {
public:
    void loadConfig(const std::string& filepath);
    void startWatching();
    void reloadConfigIfNeeded();

    std::vector<std::string> getMonitoredProcesses() const;
    std::string getProcessCommand(const std::string& process) const;
    std::string getProcessParameters(const std::string& process) const;

private:
    std::string configFilePath;
    std::unordered_map<std::string, std::pair<std::string, std::string>> processes;
    int platformWatcher;
};

#endif
