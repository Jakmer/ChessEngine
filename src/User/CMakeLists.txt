# src/User/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project(User)

# Create library User
add_library(User SHARED User.cpp User.hpp)

# include directories
target_include_directories(User PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# link libraries
#target_link_libraries(User PUBLIC )

# Add debug flags if ENABLE_DEBUG is ON
if(ENABLE_DEBUG)
    target_compile_options(User PRIVATE -g)
endif()

# Install library
install(TARGETS User DESTINATION lib)
