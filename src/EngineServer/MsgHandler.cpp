#include "MsgHandler.hpp"
#include "Message/Message.hpp"
#include <spdlog/spdlog.h>

namespace EngineServer
{
    MsgHandler::MsgHandler(bool &isRunning,
                           std::vector<std::shared_ptr<User::User>> &users,
                           std::vector<std::shared_ptr<Session::Session>> &sessions,
                           std::mutex &mtx,
                           std::string &serverName)
        : msgCreator(),
          actionHandler(std::make_shared<ActionHandler>(users, sessions, mtx, serverName)),
          isRunning(isRunning),
          users(users),
          sessions(sessions),
          mtx(mtx),
          serverName(serverName)
    {
    }

    MsgHandler::~MsgHandler()
    {
    }

    Message::Message MsgHandler::handleMsg(Message::Message &msg)
    {
        spdlog::info("EngineServer::MsgHandler Handling message");
        return proccesMessage(msg);
    }

    Message::Message MsgHandler::returnCorrectMessageType(std::string &serializedMsg)
    {
        spdlog::info("EngineServer::MsgHandler Returning correct message type");

        std::string delimiter = ";";
        std::string typeStr = serializedMsg.substr(0, serializedMsg.find(delimiter));
        int type = std::stoi(typeStr);

        switch (type)
        {
        case 0:
            return Message::Message(std::make_shared<Message::MsgConnect>(serializedMsg, true), Message::MsgType::CONNECT);
        case 1:
            return Message::Message(std::make_shared<Message::MsgLogin>(serializedMsg, true), Message::MsgType::LOGIN);
        case 2:
            return Message::Message(std::make_shared<Message::MsgGameAction>(serializedMsg, true), Message::MsgType::GAMEACTION);
        case 3:
            return Message::Message(std::make_shared<Message::MsgError>(serializedMsg, true), Message::MsgType::ERROR);
        case 4:
            return Message::Message(std::make_shared<Message::MsgDisconnect>(serializedMsg, true), Message::MsgType::DISCONNECT);
        case 5:
            return Message::Message(std::make_shared<Message::MsgAuth>(serializedMsg, true), Message::MsgType::AUTH);
        case 6:
            return Message::Message(std::make_shared<Message::MsgChat>(serializedMsg, true), Message::MsgType::CHAT);
        case 7:
            return Message::Message(std::make_shared<Message::MsgGameStateUpdate>(serializedMsg, true), Message::MsgType::GAMESTATEUPDATE);
        case 8:
            return Message::Message(std::make_shared<Message::MsgPing>(serializedMsg, true), Message::MsgType::PING);
        case 9:
            return Message::Message(std::make_shared<Message::MsgPong>(serializedMsg, true), Message::MsgType::PONG);
        case 10:
            return Message::Message(std::make_shared<Message::MsgNotification>(serializedMsg, true), Message::MsgType::NOTIFICATION);
        case 11:
            return Message::Message(std::make_shared<Message::MsgCommand>(serializedMsg, true), Message::MsgType::COMMAND);
        default:
            throw std::invalid_argument("EngineServer::MsgHandler Unknown message type");
        }
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
            spdlog::error("EngineServer::MsgHandler Unknown message type");
            std::string errorMessage = "Unknown message type";
            auto errorMsg = msgCreator.msgError(errorMessage);
            respondMsg = Message::Message(errorMsg, Message::MsgType::ERROR);
            break;
        }

        return respondMsg;
    }

    Message::Message MsgHandler::handleConnect(Message::Message &msg)
    {
        spdlog::info("EngineServer::MsgHandler Handling connect message");
        // TODO: implement part of logic here
        // For example check whether the client msg is valid as client hello etc.
        // we can also return msgCreator.msgError() or msgCreator.msgGameAction() if need to start the game immediately

        auto clientMsg = Message::MsgConnect(msg.getSerializedMsg(), true);

        spdlog::info("EngineServer::MsgHandler Client name: {}", clientMsg.name);

        std::string username = clientMsg.name;
        std::string content = clientMsg.content;

        if (!username.empty() && content == "Hello from " + username)
        {
            // notif that connection is successful. notif is for server only
            spdlog::info("EngineServer::MsgHandler Client hello received");
            auto respond = Message::Message(msgCreator.msgNotification("Connection successful", "true"), Message::MsgType::NOTIFICATION);
            return respond;
        }

        spdlog::error("EngineServer::MsgHandler Connection failed: No client hello");
        return Message::Message(msgCreator.msgNotification("Connection failed: No client hello", "false"), Message::MsgType::NOTIFICATION);
    }

    Message::Message MsgHandler::handleLogin(Message::Message /*&msg*/)
    {
        spdlog::info("EngineServer::MsgHandler Handling login message");
        // TODO: implement part of logic here
        std::string username = "";
        auto respondMsg = msgCreator.msgLogin(username);
        return Message::Message(respondMsg, Message::MsgType::LOGIN);
    }

    Message::Message MsgHandler::handleGameAction(Message::Message /*&msg*/)
    {
        spdlog::info("EngineServer::MsgHandler Handling game action message");
        // TODO: implement part of logic here
        std::string action = "";
        auto respondMsg = msgCreator.msgGameAction(action);
        return Message::Message(respondMsg, Message::MsgType::GAMEACTION);
    }

    Message::Message MsgHandler::handleError(Message::Message /*&msg*/)
    {
        spdlog::info("EngineServer::MsgHandler Handling error message");
        // TODO: implement part of logic here
        std::string errorMessage = "";
        auto respondMsg = msgCreator.msgError(errorMessage);
        return Message::Message(respondMsg, Message::MsgType::ERROR);
    }

    Message::Message MsgHandler::handleDisconnect(Message::Message /*&msg*/)
    {
        spdlog::info("EngineServer::MsgHandler Handling disconnect message");
        // TODO: implement part of logic here
        std::string reason = "";
        auto respondMsg = msgCreator.msgDisconnect(reason);
        return Message::Message(respondMsg, Message::MsgType::DISCONNECT);
    }

    Message::Message MsgHandler::handleAuth(Message::Message /*&msg*/)
    {
        spdlog::info("EngineServer::MsgHandler Handling auth message");
        // TODO: implement part of logic here
        std::string token = "";
        auto respondMsg = msgCreator.msgAuth(token);
        return Message::Message(respondMsg, Message::MsgType::AUTH);
    }

    Message::Message MsgHandler::handleChat(Message::Message /*&msg*/)
    {
        spdlog::info("EngineServer::MsgHandler Handling chat message");
        // TODO: implement part of logic here
        std::string message = "";
        auto respondMsg = msgCreator.msgChat(message);
        return Message::Message(respondMsg, Message::MsgType::CHAT);
    }

    Message::Message MsgHandler::handleGameStateUpdate(Message::Message /*&msg*/)
    {
        spdlog::info("EngineServer::MsgHandler Handling game state update message");
        // TODO: implement part of logic here
        std::string state = "";
        auto respondMsg = msgCreator.msgGameStateUpdate(state);
        return Message::Message(respondMsg, Message::MsgType::GAMESTATEUPDATE);
    }

    Message::Message MsgHandler::handlePing(Message::Message /*&msg*/)
    {
        spdlog::info("EngineServer::MsgHandler Handling ping message");
        auto respondMsg = msgCreator.msgPong();
        return Message::Message(respondMsg, Message::MsgType::PONG);
    }

    Message::Message MsgHandler::handlePong(Message::Message /*&msg*/)
    {
        spdlog::info("EngineServer::MsgHandler Handling pong message");
        // TODO: implement part of logic here
        auto respondMsg = msgCreator.msgPing();
        return Message::Message(respondMsg, Message::MsgType::PING);
    }

    Message::Message MsgHandler::handleNotification(Message::Message &msg)
    {
        spdlog::info("EngineServer::MsgHandler Handling notification message");

        auto clientMsg = Message::MsgNotification(msg.getSerializedMsg(), true);

        std::string notification = clientMsg.notification;
        std::string content = clientMsg.content;
        Message::Message actionResponse;

        // TODO: add map string->int for notification types and replace if with switch
        if (notification == "Dialog choice 0")
        {
            if (content == "1")
                actionResponse = actionHandler->joinGame();
            else if (content == "2")
                actionResponse = actionHandler->createGame();
            else if (content == "3")
                actionResponse = actionHandler->userExit();
        }
        else
            actionResponse = Message::Message(std::make_shared<Message::MsgNotification>("Unknown notification", "Null"), Message::MsgType::NOTIFICATION);
        // for recv loop stop
        isRunning = false;
        // auto respondMsg = msgCreator.msgNotification("NULL", "null");
        // return Message::Message(respondMsg, Message::MsgType::NOTIFICATION);
        return actionResponse;
    }

    Message::Message MsgHandler::handleCommand(Message::Message /*&msg*/)
    {
        spdlog::info("EngineServer::MsgHandler Handling command message");
        // TODO: implement part of logic here
        std::string command = "";
        auto respondMsg = msgCreator.msgCommand(command);
        return Message::Message(respondMsg, Message::MsgType::COMMAND);
    }

    void MsgHandler::setUser(std::shared_ptr<User::User> &user)
    {
        spdlog::info("EngineServer::MsgHandler Setting username");
        actionHandler->setUser(user);
    }
} // namespace EngineServer
