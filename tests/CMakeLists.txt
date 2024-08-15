cmake_minimum_required(VERSION 3.22.1)
project(ChessEngineTests)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(ChessEngineTests main.cpp)

target_include_directories(ChessEngineTests PRIVATE
	../src/EngineServer
	../src/Session
	../src/MessageHandler
	../src/User
	../src/Game
	../src/Message
	../src/Client
)

target_sources(ChessEngineTests PRIVATE
	EngineServerTest/EngineServerTest.cpp
	EngineServerTest/MsgHandlerTest.cpp
	ClientTest/ClientTest.cpp
	Game/GameTest.cpp
	Message/MessageTest.cpp
	Message/MsgTypesTest.cpp
	MessageHandler/MessageHandlerTest.cpp
	Session/SessionTest.cpp
	User/UserTest.cpp
)

target_link_libraries(ChessEngineTests ${GTEST_LIBRARIES} pthread
	EngineServer 
	Client
	Game
	Message
	MessageHandler
	Session
	User
)

add_test(NAME ChessEngineTests COMMAND ChessEngineTests)

install(TARGETS ChessEngineTests DESTINATION ${CMAKE_BINARY_DIR})