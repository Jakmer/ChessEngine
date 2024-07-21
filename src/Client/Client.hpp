#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <boost/asio.hpp>
#include <string>
#include <spdlog/spdlog.h>

using boost::asio::ip::tcp;
namespace Client
{

    class Client
    {
    public:
        Client(const std::string &host, const std::string &port);

        void connect();
        void receiveMessage();

    private:
        boost::asio::io_context io_context_;
        tcp::resolver resolver_;
        tcp::socket socket_;
        std::string host_;
        std::string port_;
    };
}

#endif // CLIENT_HPP
