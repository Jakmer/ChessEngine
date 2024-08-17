# scripts/CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
project(Scripts)

# Install scripts to /usr/src/app
install(PROGRAMS
    ${CMAKE_CURRENT_SOURCE_DIR}/start-client-server.sh
    ${CMAKE_CURRENT_SOURCE_DIR}/valgrind_test
    DESTINATION /usr/src/app
)