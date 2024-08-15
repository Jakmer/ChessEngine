#include "Message.hpp"

namespace Message
{
    const std::string TERMINATOR = "01111110";

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

    std::string Message::getContent() const
    {
        return msg->content;
    }
}