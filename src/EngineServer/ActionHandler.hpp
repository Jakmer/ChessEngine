#ifndef ACTION_HANDLER_HPP
#define ACTION_HANDLER_HPP

#include "Message/Message.hpp"
#include "User.hpp"
#include "Session.hpp"
#include <vector>
#include <memory>
#include <mutex>

namespace EngineServer
{
    class ActionHandler
    {
    private:
        std::shared_ptr<User::User> user;
        std::vector<std::shared_ptr<User::User>> &users;
        std::vector<std::shared_ptr<Session::Session>> &sessions;
        std::mutex &mtx;
        std::string &serverName;

    public:
        ActionHandler(std::vector<std::shared_ptr<User::User>> &users,
                      std::vector<std::shared_ptr<Session::Session>> &sessions,
                      std::mutex &mtx,
                      std::string &serverName);
        ~ActionHandler();
        virtual Message::Message joinGame(); // TODO: consider changin return type to string or sth and creating message in MsgHandler
        virtual Message::Message createGame();
        virtual Message::Message userExit();
        void setUser(std::shared_ptr<User::User> &user);
    };
}

#endif // ACTION_HANDLER_HPP