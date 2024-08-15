#ifndef MSGHANDLER_HPP
#define MSGHANDLER_HPP

#include "Message.hpp"
#include "MsgCreator.hpp"
#include "MsgTypes.hpp"

namespace EngineServer
{
    class MsgHandler
    {
    public:
        MsgHandler(bool &isRunning);
        ~MsgHandler();

        Message::Message handleMsg(Message::Message &msg);
        static Message::Message returnCorrectMessageType(std::string &serializedMsg);

    protected:
        Message::Message proccesMessage(Message::Message &msg);

        Message::Message handleConnect(Message::Message &msg);
        Message::Message handleLogin(Message::Message &msg);
        Message::Message handleGameAction(Message::Message &msg);
        Message::Message handleError(Message::Message &msg);
        Message::Message handleDisconnect(Message::Message &msg);
        Message::Message handleAuth(Message::Message &msg);
        Message::Message handleChat(Message::Message &msg);
        Message::Message handleGameStateUpdate(Message::Message &msg);
        Message::Message handlePing(Message::Message &msg);
        Message::Message handlePong(Message::Message &msg);
        Message::Message handleNotification(Message::Message &msg);
        Message::Message handleCommand(Message::Message &msg);

        EngineServer::MsgCreator msgCreator;
        bool &isRunning;
    };
}

#endif // MSGHANDLER_HPP