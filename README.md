
# Watchdog Application

## Overview
The Watchdog application is a C/C++ project designed to monitor Linux processes, with flexibility for Windows-specific implementations. It provides detailed logging, configuration management, and process monitoring functionalities, structured to support multiple platforms through an extendable API.

## Project Structure

### Root Directory
- **CMakeLists.txt**: Configuration file for building the project using CMake.

### Config
- **watchdog_config.yaml**: YAML configuration file that contains key settings for monitoring, logging levels, and paths.

### Include Directory
Contains all header files for different components of the project.

- **ConfigLoader.h**: Defines the `ConfigLoader` class responsible for loading and parsing configuration files.
- **WatchdogManager.h**: Defines the `WatchdogManager` class, the core component responsible for managing process monitoring.
- **PlatformAPI/**:
  - **PlatformAPI.h**: Interface for defining platform-specific API functions.
  - **LinuxAPI.h**: Linux-specific implementations of platform API functions for process monitoring.
  - **WindowsAPI.h**: Windows-specific implementations of platform API functions (currently inactive for Linux-only implementation).
- **utils/Logger.h**: Defines the `Logger` class, which handles log file creation and manages different logging levels (DEBUG, INFO, ERROR).

### Source Directory
Contains the implementations of core components.

- **main.cpp**: Entry point of the application, which initializes components and starts monitoring as configured.
- **WatchdogManager.cpp**: Implements the `WatchdogManager` class functions, which orchestrate monitoring based on specified configuration.
- **ConfigLoader.cpp**: Implements the `ConfigLoader` class, loading and parsing settings from `watchdog_config.yaml`.
- **PlatformAPI/**:
  - **LinuxAPI.cpp**: Implements Linux-specific process monitoring functions.
  - **WindowsAPI.cpp**: Placeholder for Windows-specific process monitoring, allowing future cross-platform compatibility.
- **utils/Logger.cpp**: Implements the `Logger` class, supporting configurable log levels and outputs to `watchdog.log`.

## Configuration
### Configuring `watchdog_config.yaml`
The `watchdog_config.yaml` file contains critical settings for the watchdog's behavior:
- **Process List**: List of target processes to monitor.
- **Command**: Invoking command to run a program.
- **Parameter List**: List of parameter passed to the process.

Example configuration:
```yaml
processes:
  - name: tmp_1
    command: ./tmp_1
    parameters: "10"
  - name: tmp_2
    command: ./tmp_2
    parameters: ""

```

## Usage

### Build Instructions
1. Install [CMake](https://cmake.org/download/).
2. In the terminal, navigate to the project root directory:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

3. This generates an executable for the watchdog application.

### Running the Application
After building the project, run the executable from the `build` directory:
```bash
./watchdog
```
The application will monitor processes as configured in `watchdog_config.yaml` and output logs to `watchdog.log`.

### Log File
Logs are stored in `watchdog.log`, where information and debug logs provide real-time status updates, and error logs flag issues. 

## Extending for Cross-Platform Compatibility
To extend the Watchdog for Windows:
1. Implement the functions in `WindowsAPI.cpp` according to Windows API calls for process monitoring.
2. Update `PlatformAPI.h` to include any necessary platform-specific function definitions.

## Future Enhancements
- **Windows Compatibility**: Complete `WindowsAPI.cpp` for cross-platform support.
- **Error Handling**: Improve error handling in configuration parsing and monitoring functions.
- **Dynamic Process Addition**: Implement live process addition to the monitored list.

## Contributing
Pull requests and issues are welcome.

---
