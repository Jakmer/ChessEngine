# main CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)

project(ChessEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# install destination
set(CMAKE_INSTALL_PREFIX /usr/local)

# Add src subdirectories
add_subdirectory(src/EngineStarter)
add_subdirectory(src/EngineServer)
add_subdirectory(src/Client)
add_subdirectory(src/ClientStarter)

# Add tests subdirectories
add_subdirectory(tests/EngineStarterTest)
