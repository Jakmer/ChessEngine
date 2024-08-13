#include "MsgTypes.hpp"
#include <iostream>
#include <vector>
#include <spdlog/spdlog.h>

namespace Message
{
    MsgConnect::MsgConnect(const std::string &name)
    {
        this->type = std::to_string(static_cast<int>(MsgType::CONNECT));
        this->name = name;
        this->content = "Hello from " + name;
    }

    MsgConnect::MsgConnect(const std::string &serializedString, bool deserialize)
    {
        if (deserialize)
        {
            this->serialized = serializedString;
            this->deserialize();
        }
        else
        {
            throw std::invalid_argument("Invalid constructor for deserialization");
        }
    }

    MsgConnect::~MsgConnect()
    {
    }

    void MsgConnect::serialize()
    {
        serialized.clear();

        serialized += type +";";
        serialized += name + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgConnect::deserialize()
    {
        std::string delimiter = ";";

        size_t pos = 0;
        std::vector<std::string> tokens;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            std::string token = serialized.substr(0, pos);
            tokens.push_back(token);
            serialized.erase(0, pos + delimiter.length());
        }

        this->type = tokens[0];
        this->name = tokens[1];
        this->content = tokens[2];

        if (serialized != TERMINATOR)
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgLogin class implementation
    MsgLogin::MsgLogin(const std::string &username)
    {
        this->type = std::to_string(static_cast<int>(MsgType::LOGIN));
        this->username = username;
    }

    MsgLogin::MsgLogin(const std::string &serializedString, bool deserialize)
    {
        if (deserialize)
        {
            this->serialized = serializedString;
            this->deserialize();
        }
        else
        {
            throw std::invalid_argument("Invalid constructor for deserialization");
        }
    }

    MsgLogin::~MsgLogin()
    {
    }

    void MsgLogin::serialize()
    {
        serialized.clear();

        serialized += type +";";
        serialized += username + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgLogin::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::vector<std::string> tokens;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            std::string token = serialized.substr(0, pos);
            tokens.push_back(token);
            serialized.erase(0, pos + delimiter.length());
        }

        this->type = tokens[0];
        this->username = tokens[1];
        this->content = tokens[2];

        if (serialized != TERMINATOR)
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgGameAction class implementation
    MsgGameAction::MsgGameAction(const std::string &action)
    {
        this->type = std::to_string(static_cast<int>(MsgType::GAMEACTION));
        this->action = action;
    }

    MsgGameAction::MsgGameAction(const std::string &serializedString, bool deserialize)
    {
        if (deserialize)
        {
            this->serialized = serializedString;
            this->deserialize();
        }
        else
        {
            throw std::invalid_argument("Invalid constructor for deserialization");
        }
    }

    MsgGameAction::~MsgGameAction()
    {
    }

    void MsgGameAction::serialize()
    {
        serialized.clear();

        serialized += type +";";
        serialized += action + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgGameAction::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::vector<std::string> tokens;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            std::string token = serialized.substr(0, pos);
            tokens.push_back(token);
            serialized.erase(0, pos + delimiter.length());
        }

        this->type = tokens[0];
        this->action = tokens[1];
        this->content = tokens[2];

        if (serialized != TERMINATOR)
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgError class implementation
    MsgError::MsgError(const std::string &errorMessage)
    {
        this->type = std::to_string(static_cast<int>(MsgType::ERROR));
        this->errorMessage = errorMessage;
    }

    MsgError::MsgError(const std::string &serializedString, bool deserialize)
    {
        if (deserialize)
        {
            this->serialized = serializedString;
            this->deserialize();
        }
        else
        {
            throw std::invalid_argument("Invalid constructor for deserialization");
        }
    }

    MsgError::~MsgError()
    {
    }

    void MsgError::serialize()
    {
        serialized.clear();

        serialized += type +";";
        serialized += errorMessage + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgError::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::vector<std::string> tokens;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            std::string token = serialized.substr(0, pos);
            tokens.push_back(token);
            serialized.erase(0, pos + delimiter.length());
        }

        this->type = tokens[0];
        this->errorMessage = tokens[1];
        this->content = tokens[2];

        if (serialized != TERMINATOR)
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgDisconnect class implementation
    MsgDisconnect::MsgDisconnect(const std::string &reason) : reason(reason)
    {
        this->type = std::to_string(static_cast<int>(MsgType::DISCONNECT));
    }

    MsgDisconnect::MsgDisconnect(const std::string &serializedString, bool deserialize)
    {
        if (deserialize)
        {
            this->serialized = serializedString;
            this->deserialize();
        }
        else
        {
            throw std::invalid_argument("Invalid constructor for deserialization");
        }
    }

    MsgDisconnect::~MsgDisconnect()
    {
    }

    void MsgDisconnect::serialize()
    {
        serialized.clear();

        serialized += type +";";
        serialized += content + ";";
        serialized += reason + ";";
        serialized += TERMINATOR;
    }

    void MsgDisconnect::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::vector<std::string> tokens;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            std::string token = serialized.substr(0, pos);
            tokens.push_back(token);
            serialized.erase(0, pos + delimiter.length());
        }

        this->type = tokens[0];
        this->content = tokens[1];
        this->reason = tokens[2];

        if (serialized != TERMINATOR)
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgAuth class implementation
    MsgAuth::MsgAuth(const std::string &token)
    {
        this->type = std::to_string(static_cast<int>(MsgType::AUTH));
        this->token = token;
    }

    MsgAuth::MsgAuth(const std::string &serializedString, bool deserialize)
    {
        if (deserialize)
        {
            this->serialized = serializedString;
            this->deserialize();
        }
        else
        {
            throw std::invalid_argument("Invalid constructor for deserialization");
        }
    }

    MsgAuth::~MsgAuth()
    {
    }

    void MsgAuth::serialize()
    {
        serialized.clear();

        serialized += type +";";
        serialized += token + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgAuth::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::vector<std::string> tokens;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            std::string token = serialized.substr(0, pos);
            tokens.push_back(token);
            serialized.erase(0, pos + delimiter.length());
        }

        this->type = tokens[0];
        this->token = tokens[1];
        this->content = tokens[2];

        if (serialized != TERMINATOR)
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgChat class implementation
    MsgChat::MsgChat(const std::string &message)
    {
        this->type = std::to_string(static_cast<int>(MsgType::CHAT));
        this->message = message;
    }

    MsgChat::MsgChat(const std::string &serializedString, bool deserialize)
    {
        if (deserialize)
        {
            this->serialized = serializedString;
            this->deserialize();
        }
        else
        {
            throw std::invalid_argument("Invalid constructor for deserialization");
        }
    }

    MsgChat::~MsgChat()
    {
    }

    void MsgChat::serialize()
    {
        serialized.clear();

        serialized += type +";";
        serialized += message + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgChat::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::vector<std::string> tokens;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            std::string token = serialized.substr(0, pos);
            tokens.push_back(token);
            serialized.erase(0, pos + delimiter.length());
        }

        this->type = tokens[0];
        this->message = tokens[1];
        this->content = tokens[2];

        if (serialized != TERMINATOR)
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgGameStateUpdate class implementation
    MsgGameStateUpdate::MsgGameStateUpdate(const std::string &state)
    {
        this->type = std::to_string(static_cast<int>(MsgType::GAMESTATEUPDATE));
        this->state = state;
    }

    MsgGameStateUpdate::MsgGameStateUpdate(const std::string &serializedString, bool deserialize)
    {
        if (deserialize)
        {
            this->serialized = serializedString;
            this->deserialize();
        }
        else
        {
            throw std::invalid_argument("Invalid constructor for deserialization");
        }
    }

    MsgGameStateUpdate::~MsgGameStateUpdate()
    {
    }

    void MsgGameStateUpdate::serialize()
    {
        serialized.clear();

        serialized += type +";";
        serialized += state + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgGameStateUpdate::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::vector<std::string> tokens;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            std::string token = serialized.substr(0, pos);
            tokens.push_back(token);
            serialized.erase(0, pos + delimiter.length());
        }

        this->type = tokens[0];
        this->state = tokens[1];
        this->content = tokens[2];

        if (serialized != TERMINATOR)
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgPing class implementation
    MsgPing::MsgPing()
    {
        this->type = std::to_string(static_cast<int>(MsgType::PING));
    }

    MsgPing::MsgPing(const std::string &serializedString, bool deserialize)
    {
        if (deserialize)
        {
            this->serialized = serializedString;
            this->deserialize();
        }
        else
        {
            throw std::invalid_argument("Invalid constructor for deserialization");
        }
    }

    MsgPing::~MsgPing()
    {
    }

    void MsgPing::serialize()
    {
        serialized.clear();

        serialized += type +";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgPing::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::vector<std::string> tokens;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            std::string token = serialized.substr(0, pos);
            tokens.push_back(token);
            serialized.erase(0, pos + delimiter.length());
        }

        this->type = tokens[0];
        this->content = tokens[1];

        if (serialized != TERMINATOR)
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgPong class implementation
    MsgPong::MsgPong()
    {
        this->type = std::to_string(static_cast<int>(MsgType::PONG));
        this->content = "Pong";
    }

    MsgPong::MsgPong(const std::string &serializedString, bool deserialize)
    {
        if (deserialize)
        {
            this->serialized = serializedString;
            this->deserialize();
        }
        else
        {
            throw std::invalid_argument("Invalid constructor for deserialization");
        }
    }

    MsgPong::~MsgPong()
    {
    }

    void MsgPong::serialize()
    {
        serialized.clear();

        serialized += type +";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgPong::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::vector<std::string> tokens;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            std::string token = serialized.substr(0, pos);
            tokens.push_back(token);
            serialized.erase(0, pos + delimiter.length());
        }

        this->type = tokens[0];
        this->content = tokens[1];

        if (serialized != TERMINATOR)
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgNotification class implementation
    MsgNotification::MsgNotification(const std::string &notification)
    {
        this->type = std::to_string(static_cast<int>(MsgType::NOTIFICATION));
        this->notification = notification;
    }

    MsgNotification::MsgNotification(const std::string &serializedString, bool deserialize)
    {
        if (deserialize)
        {
            this->serialized = serializedString;
            this->deserialize();
        }
        else
        {
            throw std::invalid_argument("Invalid constructor for deserialization");
        }
    }

    MsgNotification::~MsgNotification()
    {
    }

    void MsgNotification::serialize()
    {
        serialized.clear();

        serialized += type +";";
        serialized += notification + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgNotification::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::vector<std::string> tokens;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            std::string token = serialized.substr(0, pos);
            tokens.push_back(token);
            serialized.erase(0, pos + delimiter.length());
        }

        this->type = tokens[0];
        this->notification = tokens[1];
        this->content = tokens[2];

        if (serialized != TERMINATOR)
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgCommand class implementation
    MsgCommand::MsgCommand(const std::string &command)
    {
        this->type = std::to_string(static_cast<int>(MsgType::COMMAND));
        this->command = command;
    }

    MsgCommand::MsgCommand(const std::string &serializedString, bool deserialize)
    {
        if (deserialize)
        {
            this->serialized = serializedString;
            this->deserialize();
        }
        else
        {
            throw std::invalid_argument("Invalid constructor for deserialization");
        }
    }

    MsgCommand::~MsgCommand()
    {
    }

    void MsgCommand::serialize()
    {
        serialized.clear();

        serialized += type +";";
        serialized += command + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgCommand::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::vector<std::string> tokens;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            std::string token = serialized.substr(0, pos);
            tokens.push_back(token);
            serialized.erase(0, pos + delimiter.length());
        }

        this->type = tokens[0];
        this->command = tokens[1];
        this->content = tokens[2];

        if (serialized != TERMINATOR)
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

}