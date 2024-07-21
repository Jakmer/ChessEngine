#ifndef SESSION_HPP
#define SESSION_HPP

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp> 
#include <boost/uuid/uuid_io.hpp>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include "MessageHandler.hpp"
#include "User.hpp"
#include "Game.hpp"
#include "Message.hpp"

namespace Session
{
    class Session
    {
    public:
        Session(boost::asio::ip::tcp::socket &&socket);
        ~Session();

        void start();

        std::string getID();
    private:
        std::string sessionID;
        boost::asio::ip::tcp::socket socket;
        MessageHandler::MessageHandler messageHandler;
        User::User user;
        Game::Game game;
        bool isActive;

        Message::Message readMessage();
        void writeMessage();

    };
}

#endif // SESSION_HPP