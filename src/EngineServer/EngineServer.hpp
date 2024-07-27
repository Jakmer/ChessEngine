#ifndef ENGINESERVER_HPP
#define ENGINESERVER_HPP

#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <vector>
#include "Session.hpp"
#include "Message.hpp"

namespace EngineServer
{
    class EngineServer
    {
    public:
        EngineServer(boost::asio::io_context &ioContext, short port);
        ~EngineServer();
        void Start();
        void sendMessage(const Message::Message &msg);
        Message::Message receiveMessage();

    private:
        boost::asio::io_context &io_context_;
        boost::asio::ip::tcp::acceptor acceptor_;
        boost::asio::ip::tcp::socket socket_;
        static bool isRunning;

        void handleConnection(boost::asio::ip::tcp::socket socket);
    };
}

#endif // ENGINESERVER_HPP
