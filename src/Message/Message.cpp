#include "Message.hpp"

namespace Message
{
    Message::Message(std::string &msg)
    {
        // TODO: serialization and deserialization the message
        this->content = msg;
    }

    Message::Message(std::string &&msg)
    {
        this->content = msg;
    }

    Message::~Message()
    {
    }

    std::string Message::getContent() const
    {
        return content;
    }

    void Message::serialize()
    {

    }

    void Message::deserialize()
    {

    }
}