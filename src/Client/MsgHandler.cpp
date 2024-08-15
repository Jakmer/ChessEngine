#include "MsgHandler.hpp"
#include <memory>
#include <string>

namespace Client
{
    MsgHandler::MsgHandler()
    {
    }

    MsgHandler::~MsgHandler()
    {
    }

    Message::Message MsgHandler::handleMsg(Message::Message &msg)
    {
        return proccesMessage(msg);
    }

    Message::Message MsgHandler::proccesMessage(Message::Message &msg)
    {
        switch (msg.getType())
        {
        case Message::MsgType::CONNECT:
            return handleConnect(msg);
            break;
        case Message::MsgType::LOGIN:
            return handleLogin(msg);
            break;
        case Message::MsgType::GAMEACTION:
            return handleGameAction(msg);
            break;
        case Message::MsgType::ERROR:
            return handleError(msg);
            break;
        case Message::MsgType::DISCONNECT:
            return handleDisconnect(msg);
            break;
        case Message::MsgType::AUTH:
            return handleAuth(msg);
            break;
        case Message::MsgType::CHAT:
            return handleChat(msg);
            break;
        case Message::MsgType::GAMESTATEUPDATE:
            return handleGameStateUpdate(msg);
            break;
        case Message::MsgType::PING:
            return handlePing(msg);
            break;
        case Message::MsgType::PONG:
            return handlePong(msg);
            break;
        case Message::MsgType::NOTIFICATION:
            return handleNotification(msg);
            break;
        case Message::MsgType::COMMAND:
            return handleCommand(msg);
            break;
        default:
            std::string msgErrorReason = "Unknown message type";
            std::shared_ptr<Message::MsgInfoIfc> msgError = std::make_shared<Message::MsgError>(msgErrorReason);
            return Message::Message(msgError ,Message::MsgType::ERROR);
            break;
        }
    }

    Message::Message MsgHandler::handleConnect(Message::Message &msg)
    {
        std::string msgErrorReason = "Not implemented";
        std::shared_ptr<Message::MsgInfoIfc> msgError = std::make_shared<Message::MsgError>(msgErrorReason);
        return Message::Message(msgError, Message::MsgType::ERROR);
    }

    Message::Message MsgHandler::handleLogin(Message::Message &msg)
    {
        std::string msgErrorReason = "Not implemented";
        std::shared_ptr<Message::MsgInfoIfc> msgError = std::make_shared<Message::MsgError>(msgErrorReason);
        return Message::Message(msgError, Message::MsgType::ERROR);
    }

    Message::Message MsgHandler::handleGameAction(Message::Message &msg)
    {
        std::string msgErrorReason = "Not implemented";
        std::shared_ptr<Message::MsgInfoIfc> msgError = std::make_shared<Message::MsgError>(msgErrorReason);
        return Message::Message(msgError, Message::MsgType::ERROR);
    }

    Message::Message MsgHandler::handleError(Message::Message &msg)
    {
        std::string msgErrorReason = "Not implemented";
        std::shared_ptr<Message::MsgInfoIfc> msgError = std::make_shared<Message::MsgError>(msgErrorReason);
        return Message::Message(msgError, Message::MsgType::ERROR);
    }

    Message::Message MsgHandler::handleDisconnect(Message::Message &msg)
    {
        std::string msgErrorReason = "Not implemented";
        std::shared_ptr<Message::MsgInfoIfc> msgError = std::make_shared<Message::MsgError>(msgErrorReason);
        return Message::Message(msgError, Message::MsgType::ERROR);
    }

    Message::Message MsgHandler::handleAuth(Message::Message &msg)
    {
        std::string msgErrorReason = "Not implemented";
        std::shared_ptr<Message::MsgInfoIfc> msgError = std::make_shared<Message::MsgError>(msgErrorReason);
        return Message::Message(msgError, Message::MsgType::ERROR);
    }

    Message::Message MsgHandler::handleChat(Message::Message &msg)
    {
        std::string msgErrorReason = "Not implemented";
        std::shared_ptr<Message::MsgInfoIfc> msgError = std::make_shared<Message::MsgError>(msgErrorReason);
        return Message::Message(msgError, Message::MsgType::ERROR);
    }

    Message::Message MsgHandler::handleGameStateUpdate(Message::Message &msg)
    {
        std::string msgErrorReason = "Not implemented";
        std::shared_ptr<Message::MsgInfoIfc> msgError = std::make_shared<Message::MsgError>(msgErrorReason);
        return Message::Message(msgError, Message::MsgType::ERROR);
    }

    Message::Message MsgHandler::handlePing(Message::Message &msg)
    {
        std::string msgErrorReason = "Not implemented";
        std::shared_ptr<Message::MsgInfoIfc> msgError = std::make_shared<Message::MsgError>(msgErrorReason);
        return Message::Message(msgError, Message::MsgType::ERROR);
    }

    Message::Message MsgHandler::handlePong(Message::Message &msg)
    {
        std::string msgErrorReason = "Not implemented";
        std::shared_ptr<Message::MsgInfoIfc> msgError = std::make_shared<Message::MsgError>(msgErrorReason);
        return Message::Message(msgError, Message::MsgType::ERROR);
    }

    Message::Message MsgHandler::handleNotification(Message::Message &msg)
    {
        std::string msgErrorReason = "Not implemented";
        std::shared_ptr<Message::MsgInfoIfc> msgError = std::make_shared<Message::MsgError>(msgErrorReason);
        return Message::Message(msgError, Message::MsgType::ERROR);
    }

    Message::Message MsgHandler::handleCommand(Message::Message &msg)
    {
        std::string msgErrorReason = "Not implemented";
        std::shared_ptr<Message::MsgInfoIfc> msgError = std::make_shared<Message::MsgError>(msgErrorReason);
        return Message::Message(msgError, Message::MsgType::ERROR);
    }

} // namespace Client
