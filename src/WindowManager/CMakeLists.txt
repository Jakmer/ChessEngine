# src/WindowManager/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project(WindowManager)

# Create library WindowManager
add_library(WindowManager SHARED WindowManager.cpp WindowManager.hpp)

# Include directories
target_include_directories(WindowManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link libraries
target_link_libraries(WindowManager PUBLIC Message)

# Add debug flags if ENABLE_DEBUG is ON
if(ENABLE_DEBUG)
    target_compile_options(WindowManager PRIVATE -g)
endif()

# Install library
install(TARGETS WindowManager DESTINATION lib)