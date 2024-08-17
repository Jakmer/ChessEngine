#ifndef MOCK_ACTION_HANDLER_HPP
#define MOCK_ACTION_HANDLER_HPP

#include "gmock/gmock.h"
#include "EngineServer/ActionHandler.hpp"

class MockActionHandler : public EngineServer::ActionHandler
{
public:
    MockActionHandler(std::vector<std::shared_ptr<User::User>> &users,
                      std::vector<std::shared_ptr<Session::Session>> &sessions,
                      std::mutex &mtx,
                      std::string &serverName)
        : EngineServer::ActionHandler(users, sessions, mtx, serverName)
    {
    }
    MOCK_METHOD(Message::Message, createGame, (), (override));
    MOCK_METHOD(Message::Message, joinGame, (), (override));
    MOCK_METHOD(Message::Message, userExit, (), (override));
};

#endif // MOCK_ACTION_HANDLER_HPP