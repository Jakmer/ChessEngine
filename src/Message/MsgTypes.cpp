#include "MsgTypes.hpp"

namespace Message
{
    MsgConnect::MsgConnect(const std::string &name)
    {
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

        serialized += name + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgConnect::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::string token;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            token = serialized.substr(0, pos);
            serialized.erase(0, pos + delimiter.length());
        }

        this->name = token;

        if (serialized != std::to_string(TERMINATOR))
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgLogin class implementation
    MsgLogin::MsgLogin(const std::string &username)
    {
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

        serialized += username + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgLogin::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::string token;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            token = serialized.substr(0, pos);
            serialized.erase(0, pos + delimiter.length());
        }

        this->username = token;

        if (serialized != std::to_string(TERMINATOR))
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgGameAction class implementation
    MsgGameAction::MsgGameAction(const std::string &action)
    {
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

        serialized += action + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgGameAction::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::string token;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            token = serialized.substr(0, pos);
            serialized.erase(0, pos + delimiter.length());
        }

        this->action = token;

        if (serialized != std::to_string(TERMINATOR))
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgError class implementation
    MsgError::MsgError(const std::string &errorMessage)
    {
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

        serialized += errorMessage + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgError::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::string token;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            token = serialized.substr(0, pos);
            serialized.erase(0, pos + delimiter.length());
        }

        this->errorMessage = token;

        if (serialized != std::to_string(TERMINATOR))
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgDisconnect class implementation
    MsgDisconnect::MsgDisconnect(const std::string &reason) : reason(reason)
    {
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

        serialized += content + ";";
        serialized += reason + ";";
        serialized += TERMINATOR;
    }

    void MsgDisconnect::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::string token;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            token = serialized.substr(0, pos);
            serialized.erase(0, pos + delimiter.length());
        }

        if (serialized != std::to_string(TERMINATOR))
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgAuth class implementation
    MsgAuth::MsgAuth(const std::string &token)
    {
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

        serialized += token + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgAuth::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::string token;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            token = serialized.substr(0, pos);
            serialized.erase(0, pos + delimiter.length());
        }

        this->token = token;

        if (serialized != std::to_string(TERMINATOR))
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgChat class implementation
    MsgChat::MsgChat(const std::string &message)
    {
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

        serialized += message + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgChat::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::string token;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            token = serialized.substr(0, pos);
            serialized.erase(0, pos + delimiter.length());
        }

        this->message = token;

        if (serialized != std::to_string(TERMINATOR))
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgGameStateUpdate class implementation
    MsgGameStateUpdate::MsgGameStateUpdate(const std::string &state)
    {
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

        serialized += state + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgGameStateUpdate::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::string token;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            token = serialized.substr(0, pos);
            serialized.erase(0, pos + delimiter.length());
        }

        this->state = token;

        if (serialized != std::to_string(TERMINATOR))
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgPing class implementation
    MsgPing::MsgPing()
    {
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

        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgPing::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::string token;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            token = serialized.substr(0, pos);
            serialized.erase(0, pos + delimiter.length());
        }

        if (serialized != std::to_string(TERMINATOR))
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgPong class implementation
    MsgPong::MsgPong()
    {
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

        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgPong::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::string token;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            token = serialized.substr(0, pos);
            serialized.erase(0, pos + delimiter.length());
        }

        if (serialized != std::to_string(TERMINATOR))
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgNotification class implementation
    MsgNotification::MsgNotification(const std::string &notification)
    {
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

        serialized += notification + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgNotification::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::string token;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            token = serialized.substr(0, pos);
            serialized.erase(0, pos + delimiter.length());
        }

        this->notification = token;

        if (serialized != std::to_string(TERMINATOR))
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

    // MsgCommand class implementation
    MsgCommand::MsgCommand(const std::string &command)
    {
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

        serialized += command + ";";
        serialized += content + ";";
        serialized += TERMINATOR;
    }

    void MsgCommand::deserialize()
    {

        std::string delimiter = ";";

        size_t pos = 0;
        std::string token;
        while ((pos = serialized.find(delimiter)) != std::string::npos)
        {
            token = serialized.substr(0, pos);
            serialized.erase(0, pos + delimiter.length());
        }

        this->command = token;

        if (serialized != std::to_string(TERMINATOR))
        {
            throw std::invalid_argument("Invalid message format: No terminator found");
        }
    }

}