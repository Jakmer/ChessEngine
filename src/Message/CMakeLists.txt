# src/Message/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project(Message)

# Create library Message
add_library(Message SHARED Message.cpp Message.hpp)

# include directories
target_include_directories(Message PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install library
install(TARGETS Message DESTINATION lib)
