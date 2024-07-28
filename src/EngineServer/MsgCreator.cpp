#include "MsgCreator.hpp"

namespace EngineServer
{
    MsgCreator::MsgCreator()
    {
    }

    MsgCreator::~MsgCreator()
    {
    }

    std::shared_ptr<Message::MsgConnect> MsgCreator::msgConnect(const std::string &name)
    {
        return std::make_shared<Message::MsgConnect>(name);
    }

    std::shared_ptr<Message::MsgLogin> MsgCreator::msgLogin(const std::string &username)
    {
        return std::make_shared<Message::MsgLogin>(username);
    }

    std::shared_ptr<Message::MsgGameAction> MsgCreator::msgGameAction(const std::string &action)
    {
        return std::make_shared<Message::MsgGameAction>(action);
    }

    std::shared_ptr<Message::MsgError> MsgCreator::msgError(const std::string &errorMessage)
    {
        return std::make_shared<Message::MsgError>(errorMessage);
    }

    std::shared_ptr<Message::MsgDisconnect> MsgCreator::msgDisconnect(const std::string &reason)
    {
        return std::make_shared<Message::MsgDisconnect>(reason);
    }

    std::shared_ptr<Message::MsgAuth> MsgCreator::msgAuth(const std::string &token)
    {
        return std::make_shared<Message::MsgAuth>(token);
    }

    std::shared_ptr<Message::MsgChat> MsgCreator::msgChat(const std::string &message)
    {
        return std::make_shared<Message::MsgChat>(message);
    }

    std::shared_ptr<Message::MsgGameStateUpdate> MsgCreator::msgGameStateUpdate(const std::string &state)
    {
        return std::make_shared<Message::MsgGameStateUpdate>(state);
    }

    std::shared_ptr<Message::MsgPing> MsgCreator::msgPing()
    {
        return std::make_shared<Message::MsgPing>();
    }

    std::shared_ptr<Message::MsgPong> MsgCreator::msgPong()
    {
        return std::make_shared<Message::MsgPong>();
    }

    std::shared_ptr<Message::MsgNotification> MsgCreator::msgNotification(const std::string &notification)
    {
        return std::make_shared<Message::MsgNotification>(notification);
    }

    std::shared_ptr<Message::MsgCommand> MsgCreator::msgCommand(const std::string &command)
    {
        return std::make_shared<Message::MsgCommand>(command);
    }
}