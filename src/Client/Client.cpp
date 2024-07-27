#include "Client.hpp"

namespace Client
{

    Client::Client(const std::string &host, const std::string &port)
        : resolver_(io_context_), socket_(io_context_), host_(host), port_(port), msgQueue(), isConnected_(false)
    {
        spdlog::info("Client: Client object created");
    }

    Client::~Client()
    {
        if(isConnected_)
        {
            disconnect();
        }
    }

    void Client::connect()
    {
        try
        {
            tcp::resolver::results_type endpoints = resolver_.resolve(host_, port_);

            boost::asio::connect(socket_, endpoints);
            isConnected_ = true;

            spdlog::info("Client: Successfully connected to {}:{}", host_, port_);
        }
        catch (std::exception &e)
        {
            isConnected_ = false;
            spdlog::error("Client: Exception during connect: {}", e.what());
        }
    }

    Message::Message Client::receiveMessage()
    {
        try
        {
            boost::asio::streambuf receive_buffer;
            boost::asio::read_until(socket_, receive_buffer, '\n'); // TODO: change terminator to Message::Message::TERMINATOR

            std::istream input(&receive_buffer);
            std::string message;
            std::getline(input, message);
            auto msg = Message::Message(message);
            this->msgQueue.push(msg);

            spdlog::info("Client: Received message from server: {}", message);

            return msg;
        }
        catch (std::exception &e)
        {
            spdlog::error("Client: Exception during receiveMessage: {}", e.what());
        }
    }

    Message::Message Client::lastReceivedMessage()
    {
        return msgQueue.back();
    }

    bool Client::isConnected()
    {
        return isConnected_;
    }

    void Client::sendMessage(const Message::Message &msg)
    {
        try
        {
            boost::asio::write(socket_, boost::asio::buffer(msg.getContent()));
            spdlog::info("Client: Sent message to server: {}", msg.getContent());
        }
        catch (std::exception &e)
        {
            spdlog::error("Client: Exception during sendMessage: {}", e.what());
        }
    }

    void Client::disconnect()
    {
        try
        {
            socket_.close();
            isConnected_ = false;
            spdlog::info("Client: Disconnected from server");
        }
        catch (std::exception &e)
        {
            spdlog::error("Client: Exception during disconnect: {}", e.what());
        }
    }

}
