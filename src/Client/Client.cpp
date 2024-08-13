#include "Client.hpp"

namespace Client
{

    Client::Client(const std::string &host, const std::string &port)
        : resolver_(io_context_), socket_(io_context_), host_(host), port_(port), isConnected_(false), msgQueue()
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
            boost::asio::read_until(socket_, receive_buffer, Message::TERMINATOR);

            std::istream input(&receive_buffer);
            std::string serializedMsg;
            std::getline(input, serializedMsg);
            spdlog::info("Client: Received message from server: {}", serializedMsg);
            // TODO: here is the problem because the first string must be the message type to know which message to create
            std::shared_ptr<Message::MsgInfoIfc> msgInfo = std::make_shared<Message::MsgConnect>(serializedMsg, true);
            Message::Message msg(msgInfo, Message::MsgType::CONNECT);

            this->msgQueue.push(msg);

            return msg;
        }
        catch (std::exception &e)
        {
            spdlog::error("Client: Exception during receiveMessage: {}", e.what());
            auto msgInfo = std::make_shared<Message::MsgError>("Error: " + std::string(e.what()));
            return Message::Message(msgInfo, Message::MsgType::ERROR);
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
            std::string str = msg.getSerializedMsg();
            std::string lastEightChars = str.substr(str.size() - 8);

            if(lastEightChars != Message::TERMINATOR)
            {
                spdlog::error("Client: Message does not have a terminator at the end");
                throw std::invalid_argument("Message does not have a terminator at the end");
            }
            boost::asio::write(socket_, boost::asio::buffer(msg.getSerializedMsg()));
            spdlog::info("Client: Sent message to server {}", msg.getSerializedMsg());
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
            spdlog::info("Client: Disconnected from Wrochess");
        }
        catch (std::exception &e)
        {
            spdlog::error("Client: Exception during disconnect: {}", e.what());
        }
    }

}
