#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <memory>
#include "MsgInfoIfc.hpp"
#include "MsgTypes.hpp"

namespace Message
{
    extern const char TERMINATOR;

    enum class MsgType
    {
        CONNECT = 0,
        LOGIN,
        GAMEACTION,
        ERROR,
        DISCONNECT,
        AUTH,
        CHAT,
        GAMESTATEUPDATE,
        PING,
        PONG,
        NOTIFICATION,
        COMMAND,
    };

    class MsgInfoIfc;   // Forward declaration

    class Message
    {
    public:
        Message(const std::shared_ptr<MsgInfoIfc> &msg, const MsgType &type);
        Message() = default;
        ~Message();
        std::string getSerializedMsg() const;
        MsgType getType() const;
        bool empty() const;

    private:
        std::shared_ptr<MsgInfoIfc> msg;
        MsgType type;
    };

}

#endif // MESSAGE_HPP
