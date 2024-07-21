#ifndef ENGINESERVER_HPP
#define ENGINESERVER_HPP

#include <spdlog/spdlog.h>
#include <boost/asio.hpp>

namespace EngineServer
{
    class EngineServer
    {
    public:
        EngineServer(boost::asio::io_context &ioContext, short port);
        ~EngineServer();
        void Start();

    private:
        boost::asio::io_context &io_context_;
        boost::asio::ip::tcp::acceptor acceptor_;
        boost::asio::ip::tcp::socket socket_;
        static bool isRunning;

        void handleConnection(boost::asio::ip::tcp::socket socket);
    };
}

#endif // ENGINESERVER_HPP
