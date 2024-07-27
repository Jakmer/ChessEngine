# src/Client/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project(Client)

# Create library Client
add_library(Client SHARED Client.cpp Client.hpp)

# include directories
target_include_directories(Client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Client PUBLIC Message)

# Install library
install(TARGETS Client DESTINATION lib)
