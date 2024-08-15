#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <boost/asio.hpp>
#include <string>
#include <spdlog/spdlog.h>
#include "Message.hpp"
#include "WindowManager.hpp"
#include "MsgHandler.hpp"

#include <queue>

using boost::asio::ip::tcp;
namespace Client
{

    class Client
    {
    public:
        Client(const std::string &host, const std::string &port);
        ~Client();

        void connect();
        void disconnect();
        void sendMessage(const Message::Message &msg);
        Message::Message receiveMessage();
        Message::Message lastReceivedMessage();
        bool isConnected();
        void start();
        bool validateConnection(const Message::Message &msg);

    private:
        boost::asio::io_context io_context_;
        tcp::resolver resolver_;
        tcp::socket socket_;
        std::string host_;
        std::string port_;
        bool isConnected_;
        WindowManager::WindowManager windowManager_;
        MsgHandler msgHandler_;
        std::queue<Message::Message> msgQueue;

        friend class MsgHandler;
    };
}

#endif // CLIENT_HPP
