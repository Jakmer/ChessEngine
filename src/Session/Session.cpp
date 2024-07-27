#include "Session.hpp"

namespace Session
{
    Session::Session(boost::asio::ip::tcp::socket &&socket) : socket(std::move(socket)), isActive(true)
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

            isActive = false; // for testing purposes

            while (isActive)
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
            auto msg = Message::Message(message);

            spdlog::info("Session: Received message from client: {}", message);

            return msg;
        }
        catch (const std::exception &e)
        {
            spdlog::error("Session: Exception: {}", e.what());
            return Message::Message("Error");   // TODO: create error message
        }
    }

    void Session::writeMessage(const Message::Message &msg)
    {
        try
        {
            spdlog::info("Session: Writing message to client");
            boost::asio::write(socket, boost::asio::buffer(msg.getContent()));
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
            isActive = false;

        }
        catch (const std::exception &e)
        {
            spdlog::error("Session: Exception: {}", e.what());
        }
    }
}