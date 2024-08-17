#include "ActionHandler.hpp"

namespace EngineServer
{
    ActionHandler::ActionHandler(std::vector<std::shared_ptr<User::User>> &users,
                                 std::vector<std::shared_ptr<Session::Session>> &sessions,
                                 std::mutex &mtx,
                                 std::string &serverName)
        : user(nullptr),
          users(users),
          sessions(sessions),
          mtx(mtx),
          serverName(serverName)

    {
    }

    ActionHandler::~ActionHandler()
    {
    }

    Message::Message ActionHandler::createGame()
    {
        // Placeholder implementation
        return Message::Message();
    }

    Message::Message ActionHandler::joinGame()
    {
        // Placeholder implementation
        return Message::Message();
    }

    Message::Message ActionHandler::userExit()
    {
        // Placeholder implementation
        return Message::Message();
    }

    void ActionHandler::setUser(std::shared_ptr<User::User> &user)
    {
        this->user = user;
    }
}