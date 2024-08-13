#ifndef MSGINFO_IFC_HPP
#define MSGINFO_IFC_HPP

#include <string>
#include "Message.hpp"

namespace Message
{
    extern const std::string TERMINATOR;
    
    class MsgInfoIfc
    {
    public:
        std::string type;
        std::string content;    
        std::string serialized;

        virtual ~MsgInfoIfc() = default;
        virtual void serialize() = 0;
        virtual void deserialize() = 0;

        std::string getSerialized()
        {
            serialized = "";
            serialize();
            return serialized;
        }

    };
}

#endif // MSGINFO_IFC_HPP
