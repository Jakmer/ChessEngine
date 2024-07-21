#include "Client.hpp"

namespace Client
{

    Client::Client(const std::string &host, const std::string &port)
        : resolver_(io_context_), socket_(io_context_), host_(host), port_(port)
    {
        spdlog::info("Client: Client object created");
    }

    void Client::connect()
    {
        try
        {
            // Resolve the host and port to endpoints
            tcp::resolver::results_type endpoints = resolver_.resolve(host_, port_);

            // Connect the socket to the first endpoint
            boost::asio::connect(socket_, endpoints);

            spdlog::info("Client: Successfully connected to {}:{}", host_, port_);
        }
        catch (std::exception &e)
        {
            spdlog::error("Client: Exception during connect: {}", e.what());
        }
    }

    void Client::receiveMessage()
    {
        try
        {
            // Read the message from the server
            boost::asio::streambuf receive_buffer;
            boost::asio::read_until(socket_, receive_buffer, '\n'); // Read until newline terminator

            std::istream input(&receive_buffer);
            std::string message;
            std::getline(input, message);

            spdlog::info("Client: Received message from server: {}", message);
        }
        catch (std::exception &e)
        {
            spdlog::error("Client: Exception during receiveMessage: {}", e.what());
        }
    }

}
