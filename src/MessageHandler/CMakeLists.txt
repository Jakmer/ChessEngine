# src/MessageHandler/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project(MessageHandler)

# Create library MessageHandler
add_library(MessageHandler SHARED MessageHandler.cpp MessageHandler.hpp)

# include directories
target_include_directories(MessageHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add debug flags if ENABLE_DEBUG is ON
if(ENABLE_DEBUG)
    target_compile_options(MessageHandler PRIVATE -g)
endif()

# Install library
install(TARGETS MessageHandler DESTINATION lib)
