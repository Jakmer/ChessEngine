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

    private:
        void serialize();
        void deserialize();

        std::string content;
    };
}

#endif // MESSAGE_HPP
