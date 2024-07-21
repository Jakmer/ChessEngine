# src/Session/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project(Session)

# Create library Session
add_library(Session SHARED Session.cpp Session.hpp)

# include directories
target_include_directories(Session PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# link libraries
target_link_libraries(Session PUBLIC MessageHandler User Game Message)

# Install library
install(TARGETS Session DESTINATION lib)
