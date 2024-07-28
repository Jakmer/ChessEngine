#include "MsgHandler.hpp"
#include "Message/Message.hpp"
#include <spdlog/spdlog.h>

namespace EngineServer
{
    MsgHandler::MsgHandler()
    {
    }

    MsgHandler::~MsgHandler()
    {
    }

    Message::Message MsgHandler::handleMsg(Message::Message &msg)
    {
        spdlog::info("Handling message");
        proccesMessage(msg);
        return msg;
    }

    Message::Message MsgHandler::proccesMessage(Message::Message &msg)
    {
        auto msgType = msg.getType();
        Message::Message respondMsg;

        switch (msgType)
        {
        case Message::MsgType::CONNECT:
            respondMsg = handleConnect(msg);
            break;

        case Message::MsgType::LOGIN:
            respondMsg = handleLogin(msg);
            break;
        case Message::MsgType::GAMEACTION:
            respondMsg = handleGameAction(msg);
            break;

        case Message::MsgType::ERROR:
            respondMsg = handleError(msg);
            break;

        case Message::MsgType::DISCONNECT:
            respondMsg = handleDisconnect(msg);
            break;

        case Message::MsgType::AUTH:
            respondMsg = handleAuth(msg);
            break;

        case Message::MsgType::CHAT:
            respondMsg = handleChat(msg);
            break;

        case Message::MsgType::GAMESTATEUPDATE:
            respondMsg = handleGameStateUpdate(msg);
            break;

        case Message::MsgType::PING:
            respondMsg = handlePing(msg);
            break;

        case Message::MsgType::PONG:
            respondMsg = handlePong(msg);
            break;

        case Message::MsgType::NOTIFICATION:
            respondMsg = handleNotification(msg);
            break;

        case Message::MsgType::COMMAND:
            respondMsg = handleCommand(msg);
            break;

        default:
            spdlog::error("Unknown message type");
            std::string errorMessage = "Unknown message type";
            auto errorMsg = msgCreator.msgError(errorMessage);
            respondMsg = Message::Message(errorMsg, Message::MsgType::ERROR);
            break;
        }

        return respondMsg;
    }

    Message::Message MsgHandler::handleConnect(Message::Message &msg)
    {
        spdlog::info("Handling connect message");
        // TODO: implement part of logic here
        // For example check whether the client msg is valid as client hello etc.
        // we can also return msgCreator.msgError() or msgCreator.msgGameAction() if need to start the game immediately

        // dynamic cast to resolve polymorphism
        auto clientMsg = Message::MsgConnect(msg.getSerializedMsg());

        // now we can access the fields of MsgConnect
        spdlog::info("Client name: {}", clientMsg.name);

        // logic here
        std::string name = "Wrochess"; // TODO: add and replace server name
        
        auto respondMsg = msgCreator.msgConnect(name);

        return Message::Message(respondMsg, Message::MsgType::CONNECT);
    }

    Message::Message MsgHandler::handleLogin(Message::Message &msg)
    {
        spdlog::info("Handling login message");
        // TODO: implement part of logic here
        std::string username = "";
        auto respondMsg = msgCreator.msgLogin(username);
        return Message::Message(respondMsg, Message::MsgType::LOGIN);
    }

    Message::Message MsgHandler::handleGameAction(Message::Message &msg)
    {
        spdlog::info("Handling game action message");
        // TODO: implement part of logic here
        std::string action = "";
        auto respondMsg = msgCreator.msgGameAction(action);
        return Message::Message(respondMsg, Message::MsgType::GAMEACTION);
    }

    Message::Message MsgHandler::handleError(Message::Message &msg)
    {
        spdlog::info("Handling error message");
        // TODO: implement part of logic here
        std::string errorMessage = "";
        auto respondMsg = msgCreator.msgError(errorMessage);
        return Message::Message(respondMsg, Message::MsgType::ERROR);
    }

    Message::Message MsgHandler::handleDisconnect(Message::Message &msg)
    {
        spdlog::info("Handling disconnect message");
        // TODO: implement part of logic here
        std::string reason = "";
        auto respondMsg = msgCreator.msgDisconnect(reason);
        return Message::Message(respondMsg, Message::MsgType::DISCONNECT);
    }

    Message::Message MsgHandler::handleAuth(Message::Message &msg)
    {
        spdlog::info("Handling auth message");
        // TODO: implement part of logic here
        std::string token = "";
        auto respondMsg = msgCreator.msgAuth(token);
        return Message::Message(respondMsg, Message::MsgType::AUTH);
    }

    Message::Message MsgHandler::handleChat(Message::Message &msg)
    {
        spdlog::info("Handling chat message");
        // TODO: implement part of logic here
        std::string message = "";
        auto respondMsg = msgCreator.msgChat(message);
        return Message::Message(respondMsg, Message::MsgType::CHAT);
    }

    Message::Message MsgHandler::handleGameStateUpdate(Message::Message &msg)
    {
        spdlog::info("Handling game state update message");
        // TODO: implement part of logic here
        std::string state = "";
        auto respondMsg = msgCreator.msgGameStateUpdate(state);
        return Message::Message(respondMsg, Message::MsgType::GAMESTATEUPDATE);
    }

    Message::Message MsgHandler::handlePing(Message::Message &msg)
    {
        spdlog::info("Handling ping message");
        auto respondMsg = msgCreator.msgPong();
        return Message::Message(respondMsg, Message::MsgType::PONG);
    }

    Message::Message MsgHandler::handlePong(Message::Message &msg)
    {
        spdlog::info("Handling pong message");
        // TODO: implement part of logic here
        auto respondMsg = msgCreator.msgPing();
        return Message::Message(respondMsg, Message::MsgType::PING);
    }

    Message::Message MsgHandler::handleNotification(Message::Message &msg)
    {
        spdlog::info("Handling notification message");
        // TODO: implement part of logic here
        std::string notification = "";
        auto respondMsg = msgCreator.msgNotification(notification);
        return Message::Message(respondMsg, Message::MsgType::NOTIFICATION);
    }

    Message::Message MsgHandler::handleCommand(Message::Message &msg)
    {
        spdlog::info("Handling command message");
        // TODO: implement part of logic here
        std::string command = "";
        auto respondMsg = msgCreator.msgCommand(command);
        return Message::Message(respondMsg, Message::MsgType::COMMAND);
    }
}