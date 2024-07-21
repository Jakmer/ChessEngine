#include "EngineServer.hpp"

namespace EngineServer
{
    bool EngineServer::isRunning = false;

    EngineServer::EngineServer(boost::asio::io_context &ioContext, short port) : io_context_(ioContext),
                                                                                 acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
                                                                                 socket_(io_context_)
    {
        spdlog::info("EngineServer: EngineServer constructor");
    }

    EngineServer::~EngineServer()
    {
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

}