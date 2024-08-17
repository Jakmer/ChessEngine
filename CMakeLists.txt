# main CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)

project(ChessEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -pedantic)

# Enable ccache
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

# Set cmake generator
set(CMAKE_GENERATOR "Ninja")

# install destination
set(CMAKE_INSTALL_PREFIX /usr/local)

# Define the debug flag
option(ENABLE_DEBUG "Enable debug mode" ON)

if(ENABLE_DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

# Add src subdirectories
add_subdirectory(src/EngineStarter)
add_subdirectory(src/EngineServer)
add_subdirectory(src/Client)
add_subdirectory(src/ClientStarter)
add_subdirectory(src/Session)
add_subdirectory(src/Message)
add_subdirectory(src/MessageHandler)
add_subdirectory(src/Game)
add_subdirectory(src/User)
add_subdirectory(src/WindowManager)

# Add tests subdirectories
add_subdirectory(tests)

# Add scripts subdirectory
add_subdirectory(scripts)
