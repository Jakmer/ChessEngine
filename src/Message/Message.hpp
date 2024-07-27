#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

namespace Message
{
    class Message
    {
    public:
        Message(std::string &msg);
        Message(std::string &&msg);
        ~Message();
        std::string getContent() const;
        void serialize();
        void deserialize();

    private:

        std::string content;
    };
}

#endif // MESSAGE_HPP
