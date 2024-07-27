#include "EngineServer.hpp"

namespace EngineServer
{
    bool EngineServer::isRunning = false;

    EngineServer::EngineServer(boost::asio::io_context &ioContext, short port) : io_context_(ioContext),
                                                                                 acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
                                                                                 socket_(io_context_)
    {
        if (port < 0)
        {
            throw std::invalid_argument("Port number must be greater than 0");  // TODO: Consider createing exception class
        }
        spdlog::info("EngineServer: EngineServer constructor");
    }

    EngineServer::~EngineServer()
    {
        if(acceptor_.is_open())
        {
            acceptor_.close();
            io_context_.stop();
        }
        spdlog::info("EngineServer: EngineServer destructor");
    }

    void EngineServer::Start()
    {
        spdlog::info("EngineServer: EngineServer started accepting connections");
        isRunning = true;

        while (isRunning)
        {
            boost::asio::ip::tcp::socket socket(io_context_);
            boost::system::error_code ec;
            acceptor_.accept(socket, ec);
            if (ec)
            {
                spdlog::error("EngineServer: Error accepting connection: {}", ec.message());
                continue;
            }
            std::thread(&EngineServer::handleConnection, this, std::move(socket)).detach();
        }

        spdlog::info("EngineServer: EngineServer stopped accepting connections");
    }

    void EngineServer::handleConnection(boost::asio::ip::tcp::socket socket)
    {
        spdlog::info("EngineServer: Connection accepted");
        
        auto session = std::make_shared<Session::Session>(std::move(socket));
        session->start();

        spdlog::info("EngineServer: Connection closed");
    }

    void EngineServer::sendMessage(const Message::Message &msg)
    {
        spdlog::info("EngineServer: Sending message to client: {}", msg.getContent());
        try
        {
            boost::asio::write(socket_, boost::asio::buffer(msg.getContent()));
        }
        catch(const std::exception& e)
        {
            spdlog::error("EngineServer: Exception during sendMessage: {}", e.what());
        }
        
    }

    Message::Message EngineServer::receiveMessage()
    {
        try
        {
            boost::asio::streambuf receive_buffer;
            boost::asio::read_until(socket_, receive_buffer, '\n'); ?// TODO: change terminator to Message::Message::TERMINATOR

            std::istream input(&receive_buffer);
            std::string message;
            std::getline(input, message);
            auto msg = Message::Message(message);

            spdlog::info("EngineServer: Received message from client: {}", message);

            return msg;
        }
        catch(const std::exception& e)
        {
            spdlog::error("EngineServer: Exception during receiveMessage: {}", e.what());
        }
    }

}