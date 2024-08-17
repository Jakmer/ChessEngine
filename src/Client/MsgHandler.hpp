#ifndef CLIENT_MSGHANDLER_HPP
#define CLIENT_MSGHANDLER_HPP

#include "Message.hpp"

namespace Client
{
    class MsgHandler
    {
    public:
        MsgHandler();
        ~MsgHandler();

        Message::Message proccesMessage(Message::Message &msg);
        Message::Message handleMsg(Message::Message &msg);
        Message::Message handleConnect(Message::Message /*&msg*/);
        Message::Message handleLogin(Message::Message /*&msg*/);
        Message::Message handleGameAction(Message::Message /*&msg*/);
        Message::Message handleError(Message::Message /*&msg*/);
        Message::Message handleDisconnect(Message::Message /*&msg*/);
        Message::Message handleAuth(Message::Message /*&msg*/);
        Message::Message handleChat(Message::Message /*&msg*/);
        Message::Message handleGameStateUpdate(Message::Message /*&msg*/);
        Message::Message handlePing(Message::Message /*&msg*/);
        Message::Message handlePong(Message::Message /*&msg*/);
        Message::Message handleNotification(Message::Message /*&msg*/);
        Message::Message handleCommand(Message::Message /*&msg*/);
    };
}

#endif // CLIENT_MSGHANDLER_HPP