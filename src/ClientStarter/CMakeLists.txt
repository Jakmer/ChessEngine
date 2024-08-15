# src/ClientStarter/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project(ClientStarter)

# Create executable ClientStarter
add_executable(ClientStarter ClientStarter.cpp)

# Link library EngineServer
target_link_libraries(ClientStarter PRIVATE Client)

# Include EngineServer headers
target_include_directories(ClientStarter PRIVATE ../Client)

# Add debug flags if ENABLE_DEBUG is ON
if(ENABLE_DEBUG)
    target_compile_options(ClientStarter PRIVATE -g)
endif()

# Install executable
install(TARGETS ClientStarter DESTINATION bin)
