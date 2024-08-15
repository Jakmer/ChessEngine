#include "Session.hpp"
#include "MsgInfoIfc.hpp"


namespace Session
{
    Session::Session(boost::asio::ip::tcp::socket &&socket, User::User &user) : socket(std::move(socket)), isActive_(true), user(user)
    {
        try
        {
            spdlog::info("Session: Session constructor");
            boost::uuids::random_generator gen;
            boost::uuids::uuid id = gen();
            sessionID = boost::uuids::to_string(id);
        }
        catch (const std::exception &e)
        {
            spdlog::error("Session: Exception: {}", e.what());
        }
    }

    Session::~Session()
    {
        spdlog::info("Session: Session destructor");
    }

    std::string Session::getID()
    {
        return sessionID;
    }

    void Session::start()
    {
        try
        {
            spdlog::info("Session: Session started");

            isActive_ = false; // for testing purposes

            while (isActive_)
            {
                // TODO: implement timeout for readMessage
                auto msg = readMessage();
                // auto response =messageHandler.handleMessage(msg);
                // writeMessage(response);
            }
        }
        catch (const std::exception &e)
        {
            spdlog::error("Session: Exception: {}", e.what());
        }
    }

    Message::Message Session::readMessage()
    {
        try
        {
            boost::asio::streambuf receive_buffer;
            boost::asio::read_until(socket, receive_buffer, '\n'); 

            std::istream input(&receive_buffer);
            std::string message;
            std::getline(input, message);
            auto msgInfo = std::make_shared<Message::MsgConnect>(message);
            auto msg = Message::Message(msgInfo, Message::MsgType::CONNECT);        // chenge connect

            spdlog::info("Session: Received message from client");

            return msg;
        }
        catch (const std::exception &e)
        {
            spdlog::error("Session: Exception: {}", e.what());
            auto msgInfo = std::make_shared<Message::MsgError>("Error: " + std::string(e.what()));
            return Message::Message(msgInfo, Message::MsgType::ERROR);
        }
    }

    void Session::writeMessage(const Message::Message &msg)
    {
        if(msg.empty())
        {
            spdlog::error("Session: Empty message");
            throw std::invalid_argument("Empty message");
        }
        try
        {
            spdlog::info("Session: Writing message to client");
            boost::asio::write(socket, boost::asio::buffer(msg.getSerializedMsg()));
        }
        catch (const std::exception &e)
        {
            spdlog::error("Session: Exception: {}", e.what());
        }
    }

    void Session::stop()
    {
        try
        {
            spdlog::info("Session: Session stopped");
            isActive_ = false;

        }
        catch (const std::exception &e)
        {
            spdlog::error("Session: Exception: {}", e.what());
        }
    }

    bool Session::isActive()
    {
        return isActive_;
    }
}