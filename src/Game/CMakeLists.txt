# src/Game/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project(Game)

# Create library Game
add_library(Game SHARED Game.cpp Game.hpp)

# include directories
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# link libraries
#target_link_libraries(Game PUBLIC)

# Install library
install(TARGETS Game DESTINATION lib)
