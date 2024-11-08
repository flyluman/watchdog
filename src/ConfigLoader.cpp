#include "ConfigLoader.h"
#include "utils/Logger.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <thread>
#include <chrono>

#ifdef __linux__
#include <sys/inotify.h>
#include <unistd.h>
#endif

void ConfigLoader::loadConfig(const std::string& filepath) {
    configFilePath = filepath;
    YAML::Node config = YAML::LoadFile(filepath);
    processes.clear();

    for (const auto& process : config["processes"]) {
        std::string name = process["name"].as<std::string>();
        std::string command = process["command"].as<std::string>();
        std::string parameters = process["parameters"].as<std::string>();
        processes[name] = {command, parameters};
        Logger::log("Loaded process " + name + " with command: " + command + " with parameters: " + parameters);
    }
}

void ConfigLoader::startWatching() {
#ifdef __linux__
    platformWatcher = inotify_init();
    if (platformWatcher < 0) {
        Logger::log("Failed to initialize inotify.");
        return;
    }
    inotify_add_watch(platformWatcher, configFilePath.c_str(), IN_MODIFY);
#endif
}

void ConfigLoader::reloadConfigIfNeeded() {
#ifdef __linux__
    char buffer[1024];
    int length = read(platformWatcher, buffer, 1024);
    if (length > 0) {
        Logger::log("Configuration file modified. Reloading configuration.");
        loadConfig(configFilePath);
    }
#endif
}

std::vector<std::string> ConfigLoader::getMonitoredProcesses() const {
    std::vector<std::string> processNames;
    for (const auto& [name, _] : processes) {
        processNames.push_back(name);
    }
    return processNames;
}

std::string ConfigLoader::getProcessCommand(const std::string& process) const {
    auto it = processes.find(process);
    if (it != processes.end()) {
        return it->second.first;
    }
    return "";
}

std::string ConfigLoader::getProcessParameters(const std::string& process) const {
    auto it = processes.find(process);
    if (it != processes.end()) {
        return it->second.second;
    }
    return "";
}
