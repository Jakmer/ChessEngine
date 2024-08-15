#ifndef MSGCREATOR_HPP
#define MSGCREATOR_HPP

#include "Message.hpp"
#include "MsgTypes.hpp"
#include <memory>

namespace EngineServer
{
    class MsgCreator
    {
    public:
        MsgCreator();
        ~MsgCreator();

        std::shared_ptr<Message::MsgConnect> msgConnect(const std::string &name);
        std::shared_ptr<Message::MsgLogin> msgLogin(const std::string &username);
        std::shared_ptr<Message::MsgGameAction> msgGameAction(const std::string &action);
        std::shared_ptr<Message::MsgError> msgError(const std::string &errorMessage);
        std::shared_ptr<Message::MsgDisconnect> msgDisconnect(const std::string &reason);
        std::shared_ptr<Message::MsgAuth> msgAuth(const std::string &token);
        std::shared_ptr<Message::MsgChat> msgChat(const std::string &message);
        std::shared_ptr<Message::MsgGameStateUpdate> msgGameStateUpdate(const std::string &state);
        std::shared_ptr<Message::MsgPing> msgPing();
        std::shared_ptr<Message::MsgPong> msgPong();
        std::shared_ptr<Message::MsgNotification> msgNotification(const std::string &notification, const std::string &details);
        std::shared_ptr<Message::MsgCommand> msgCommand(const std::string &command);
    };
}

#endif // MSGCREATOR_HPP