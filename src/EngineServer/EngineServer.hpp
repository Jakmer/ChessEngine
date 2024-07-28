#ifndef ENGINESERVER_HPP
#define ENGINESERVER_HPP

#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <vector>
#include "Session.hpp"
#include "Message.hpp"
#include "MsgCreator.hpp"
#include "MsgHandler.hpp"
#include "MsgTypes.hpp"

#include "User.hpp"
#include <mutex>

namespace EngineServer
{
    class EngineServer
    {
    public:
        EngineServer(boost::asio::io_context &ioContext, short port);
        ~EngineServer();
        void Start();
        void Stop();
        void sendMessage(const Message::Message &msg, boost::asio::ip::tcp::socket &socket);
        Message::Message receiveMessage(boost::asio::ip::tcp::socket &socket);
        void setClientLimit(int limit);
        int getClientLimit();
        static bool isRunning();

    private:
        boost::asio::io_context &io_context_;
        boost::asio::ip::tcp::acceptor acceptor_;
        boost::asio::ip::tcp::socket socket_;
        static bool isRunning_;
        bool isAccepting;
        int clientLimit = 0;
        std::vector<std::shared_ptr<User::User>> users;
        std::vector<std::shared_ptr<Session::Session>> sessions;
        std::vector<std::thread> connections;
        std::mutex mtx;


        void handleConnection(boost::asio::ip::tcp::socket socket);
    };
}

#endif // ENGINESERVER_HPP
