# src/EngineServer/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project(EngineServer)

# Create library EngineServer
add_library(EngineServer SHARED EngineServer.cpp EngineServer.hpp)

# include directories
target_include_directories(EngineServer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install library
install(TARGETS EngineServer DESTINATION lib)
