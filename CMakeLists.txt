cmake_minimum_required(VERSION 3.22.1)

project(ChessEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src/EngineStarter)
add_subdirectory(tests/EngineStarterTest)
