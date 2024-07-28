#include "Message.hpp"

namespace Message
{
    const char TERMINATOR = '\0';

    Message::Message(const std::shared_ptr<MsgInfoIfc> &msg, const MsgType &type)
        : msg(msg), type(type)
    {
    }

    Message::~Message()
    {
    }

    std::string Message::getSerializedMsg() const
    {
        return msg->getSerialized();
    }

    MsgType Message::getType() const
    {
        return type;
    }

    bool Message::empty() const
    {
        return msg->content.empty();    // TODO: improve this
    }
}