#ifndef MSGHANDLER_HPP
#define MSGHANDLER_HPP

#include "Message.hpp"
#include "MsgCreator.hpp"
#include "MsgTypes.hpp"
#include "ActionHandler.hpp"
#include "User.hpp"
#include "Session.hpp"
#include <memory>
#include <vector>
#include <mutex>

namespace EngineServer
{
    class MsgHandler
    {
    public:
        MsgHandler(bool &isRunning,
                   std::vector<std::shared_ptr<User::User>> &users,
                   std::vector<std::shared_ptr<Session::Session>> &sessions,
                   std::mutex &mtx,
                   std::string &serverName);
        ~MsgHandler();

        Message::Message handleMsg(Message::Message &msg);
        void setUser(std::shared_ptr<User::User> &user);
        static Message::Message returnCorrectMessageType(std::string &serializedMsg);

    protected:
        Message::Message proccesMessage(Message::Message &msg);

        Message::Message handleConnect(Message::Message &msg);
        Message::Message handleLogin(Message::Message /*&msg*/);
        Message::Message handleGameAction(Message::Message /*&msg*/);
        Message::Message handleError(Message::Message /*&msg*/);
        Message::Message handleDisconnect(Message::Message /*&msg*/);
        Message::Message handleAuth(Message::Message /*&msg*/);
        Message::Message handleChat(Message::Message /*&msg*/);
        Message::Message handleGameStateUpdate(Message::Message /*&msg*/);
        Message::Message handlePing(Message::Message /*&msg*/);
        Message::Message handlePong(Message::Message /*&msg*/);
        Message::Message handleNotification(Message::Message &msg);
        Message::Message handleCommand(Message::Message /*&msg*/);

        EngineServer::MsgCreator msgCreator;
        std::shared_ptr<ActionHandler> actionHandler;
        bool &isRunning;
        std::vector<std::shared_ptr<User::User>> &users;
        std::vector<std::shared_ptr<Session::Session>> &sessions;
        std::mutex &mtx;
        std::string &serverName;
    };
}

#endif // MSGHANDLER_HPP