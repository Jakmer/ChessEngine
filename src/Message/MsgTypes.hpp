#ifndef MESSAGE_TYPES_HPP
#define MESSAGE_TYPES_HPP

#include <string>
#include <stdexcept>
#include "MsgInfoIfc.hpp"

namespace Message
{
    extern const char TERMINATOR;

    class MsgConnect : public MsgInfoIfc
    {
    public:
        MsgConnect(const std::string &name);
        MsgConnect(const std::string &serializedString, bool deserialize);
        ~MsgConnect();

        void serialize() override;
        void deserialize() override;

        std::string name;
    };

    class MsgLogin : public MsgInfoIfc
    {
    public:
        MsgLogin(const std::string &username);
        MsgLogin(const std::string &serializedString, bool deserialize);
        ~MsgLogin();

        void serialize() override;
        void deserialize() override;

        std::string username;
    };

    class MsgGameAction : public MsgInfoIfc
    {
    public:
        MsgGameAction(const std::string &action);
        MsgGameAction(const std::string &serializedString, bool deserialize);
        ~MsgGameAction();

        void serialize() override;
        void deserialize() override;

        std::string action;
    };

    class MsgError : public MsgInfoIfc
    {
    public:
        MsgError(const std::string &errorMessage);
        MsgError(const std::string &serializedString, bool deserialize);
        ~MsgError();

        void serialize() override;
        void deserialize() override;

        std::string errorMessage;
    };

    class MsgDisconnect : public MsgInfoIfc
    {
    public:
        MsgDisconnect(const std::string &reason);
        MsgDisconnect(const std::string &serializedString, bool deserialize);
        ~MsgDisconnect();

        void serialize() override;
        void deserialize() override;

        std::string reason;
    };

    class MsgAuth : public MsgInfoIfc
    {
    public:
        MsgAuth(const std::string &token);
        MsgAuth(const std::string &serializedString, bool deserialize);
        ~MsgAuth();

        void serialize() override;
        void deserialize() override;

        std::string token;
    };

    class MsgChat : public MsgInfoIfc
    {
    public:
        MsgChat(const std::string &message);
        MsgChat(const std::string &serializedString, bool deserialize);
        ~MsgChat();

        void serialize() override;
        void deserialize() override;

        std::string message;
    };

    class MsgGameStateUpdate : public MsgInfoIfc
    {
    public:
        MsgGameStateUpdate(const std::string &state);
        MsgGameStateUpdate(const std::string &serializedString, bool deserialize);
        ~MsgGameStateUpdate();

        void serialize() override;
        void deserialize() override;

        std::string state;
    };

    class MsgPing : public MsgInfoIfc
    {
    public:
        MsgPing();
        MsgPing(const std::string &serializedString, bool deserialize);
        ~MsgPing();

        void serialize() override;
        void deserialize() override;
    };

    class MsgPong : public MsgInfoIfc
    {
    public:
        MsgPong();
        MsgPong(const std::string &serializedString, bool deserialize);
        ~MsgPong();

        void serialize() override;
        void deserialize() override;
    };

    class MsgNotification : public MsgInfoIfc
    {
    public:
        MsgNotification(const std::string &notification);
        MsgNotification(const std::string &serializedString, bool deserialize);
        ~MsgNotification();

        void serialize() override;
        void deserialize() override;

        std::string notification;
    };

    class MsgCommand : public MsgInfoIfc
    {
    public:
        MsgCommand(const std::string &command);
        MsgCommand(const std::string &serializedString, bool deserialize);
        ~MsgCommand();

        void serialize() override;
        void deserialize() override;

        std::string command;
    };
}

#endif // MESSAGE_TYPES_HPP