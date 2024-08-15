# src/EngineStarter/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project(EngineStarter)

# Create executable EngineStarter
add_executable(EngineStarter EngineStarter.cpp)

# Link library EngineServer
target_link_libraries(EngineStarter PRIVATE EngineServer User)

# Include EngineServer headers
target_include_directories(EngineStarter PRIVATE ../EngineServer ../User)

# Add debug flags if ENABLE_DEBUG is ON
if(ENABLE_DEBUG)
    target_compile_options(EngineStarter PRIVATE -g)
endif()

# Install executable
install(TARGETS EngineStarter DESTINATION bin)
