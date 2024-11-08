cmake_minimum_required(VERSION 3.10)
project(watchdog)

set(CMAKE_CXX_STANDARD 17)

# Add source files
set(SRC_FILES
    src/main.cpp
    src/WatchdogManager.cpp
    src/ConfigLoader.cpp
    src/PlatformAPI/LinuxAPI.cpp
    src/utils/Logger.cpp
)

# Add executable
add_executable(watchdog ${SRC_FILES})

# Include directories
target_include_directories(watchdog PRIVATE include)

# Link libraries
target_link_libraries(watchdog yaml-cpp)

# Compiler warnings
if (MSVC)
    target_compile_options(watchdog PRIVATE /W4)
else()
    target_compile_options(watchdog PRIVATE -Wall -Wextra -pedantic)
endif()
