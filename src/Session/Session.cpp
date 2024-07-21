#include "Session.hpp"

namespace Session
{
    Session::Session(boost::asio::ip::tcp::socket &&socket): socket(std::move(socket)), isActive(true)
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

            writeMessage(); // Server hello message

            isActive = false;   // for testing purposes
            
            while (isActive)
            {
                // TODO: implement timeout for readMessage
                auto msg = readMessage();
                //auto response =messageHandler.handleMessage(msg);
                //writeMessage(response);                   
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
            
        }
        catch (const std::exception &e)
        {
            spdlog::error("Session: Exception: {}", e.what());
        }
    }

    void Session::writeMessage()
    {
        try
        {
            spdlog::info("Session: Writing message to client");
            std::string message = "Hello from server\n";
            boost::asio::write(socket, boost::asio::buffer(message));
        }
        catch (const std::exception &e)
        {
            spdlog::error("Session: Exception: {}", e.what());
        }
    }
}