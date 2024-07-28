#ifndef MSGCREATOR
#define MSGCREATOR

#include "Message.hpp"
#include "Message/MsgConnect.hpp"

namespace EngineServer
{
    class MsgCreator
    {
    public:
        MsgCreator();
        ~MsgCreator();

        Message::MsgConnect msgConnect();
    };
}


#endif // MSGCREATOR