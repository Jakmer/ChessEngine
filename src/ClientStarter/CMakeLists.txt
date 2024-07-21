# src/ClientStarter/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project(ClientStarter)

# Create executable ClientStarter
add_executable(ClientStarter ClientStarter.cpp)

# Link library EngineServer
target_link_libraries(ClientStarter PRIVATE Client)

# Include EngineServer headers
target_include_directories(ClientStarter PRIVATE ../Client)

# Install executable
install(TARGETS ClientStarter DESTINATION bin)
