# src/Client/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project(Client)

# Create library Client
add_library(Client SHARED 
    Client.cpp
    Client.hpp
    MsgHandler.cpp
    MsgHandler.hpp)

# include directories
target_include_directories(Client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/)

target_link_libraries(Client PUBLIC Message WindowManager)

# Add debug flags if ENABLE_DEBUG is ON
if(ENABLE_DEBUG)
    target_compile_options(Client PRIVATE -g)
endif()

# Install library
install(TARGETS Client DESTINATION lib)
