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
	../src/WindowManager
)

target_sources(ChessEngineTests PRIVATE
	EngineServerTest/EngineServerTest.cpp
	EngineServerTest/MsgHandlerTest.cpp
	ClientTest/ClientTest.cpp
	ClientTest/ClientMsgHandlerTest.cpp
	Game/GameTest.cpp
	Message/MessageTest.cpp
	Message/MsgTypesTest.cpp
	MessageHandler/MessageHandlerTest.cpp
	Session/SessionTest.cpp
	User/UserTest.cpp
	WindowManager/WindowManagerTest.cpp
)

target_link_libraries(ChessEngineTests ${GTEST_LIBRARIES} 
	gmock
	pthread
	EngineServer 
	Client
	Game
	Message
	MessageHandler
	Session
	User
	WindowManager
)

add_test(NAME ChessEngineTests COMMAND ChessEngineTests)

install(TARGETS ChessEngineTests DESTINATION ${CMAKE_BINARY_DIR})

# Add custom target to run tests with Valgrind
add_custom_target(ValgrindTest
    COMMAND valgrind --leak-check=full --log-file=valgrind_test.log $<TARGET_FILE:ChessEngineTests>
    DEPENDS ChessEngineTests
    COMMENT "Running ChessEngineTests with Valgrind"
)
