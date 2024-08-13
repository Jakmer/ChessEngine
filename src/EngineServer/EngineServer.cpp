#include "EngineServer.hpp"

namespace EngineServer
{
    bool EngineServer::isRunning_ = false;

    EngineServer::EngineServer(boost::asio::io_context &ioContext, short port) : io_context_(ioContext),
                                                                                 acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
                                                                                 socket_(io_context_),
                                                                                 isAccepting(true),
                                                                                 clientLimit(30),
                                                                                 users(),
                                                                                 sessions(),
                                                                                 connections(),
                                                                                 mtx()
    {
        if (port < 0)
        {
            throw std::invalid_argument("Port number must be greater than 0"); // TODO: Consider createing exception class
        }
        spdlog::info("EngineServer: EngineServer constructor");
    }

    EngineServer::~EngineServer()
    {
        spdlog::info("EngineServer: EngineServer destructor");

        if (acceptor_.is_open())
        {
            acceptor_.close();
            io_context_.stop();
        }
        spdlog::info("EngineServer: EngineServer stopped");
    }

    void EngineServer::Start()
    {
        spdlog::info("EngineServer: EngineServer started accepting connections");
        isRunning_ = true;

        while (isRunning_)
        {
            spdlog::info("EngineServer: Client limit: {}", clientLimit);
            if (clientLimit == 0)
            {
                spdlog::info("EngineServer: Client limit reached");
                isAccepting = false;
            }
            boost::asio::ip::tcp::socket socket(io_context_);
            boost::system::error_code ec;
            acceptor_.accept(socket, ec);
            if (ec)
            {
                spdlog::error("EngineServer: Error accepting connection: {}", ec.message());
                continue;
            }
            connections.emplace_back(&EngineServer::handleConnection, this, std::move(socket));
            clientLimit--;
            spdlog::info("EngineServer: Connection thread started");
        }

        Stop();

        spdlog::info("EngineServer: EngineServer stopped accepting connections");
    }

    void EngineServer::handleConnection(boost::asio::ip::tcp::socket socket)
    {
        spdlog::info("EngineServer: Connection accepted");

        MsgCreator msgCreator;
        MsgHandler msgHandler;
        std::string name = "Wrochess";
        auto connectMsgInfo = msgCreator.msgConnect(name);

        auto connectMsg = Message::Message(connectMsgInfo, Message::MsgType::CONNECT);
        // TODO: try to implement function for faster creating messages in EnginveServe
        spdlog::info("EngineServer: Sending connection message to client {}", connectMsg.getSerializedMsg());
        sendMessage(connectMsg, socket);

        // TODO: implement timeout for receiving message

        auto respondMsg = receiveMessage(socket);

        msgHandler.handleMsg(respondMsg);

        // auto user = std::make_shared<User::User>();
        // auto session = std::make_shared<Session::Session>(std::move(socket));

        mtx.lock();
        // users.push_back(user);
        // sessions.push_back(session);
        mtx.unlock();

        // session->start();

        spdlog::info("EngineServer: Connection closed");
    }

    void EngineServer::sendMessage(const Message::Message &msg, boost::asio::ip::tcp::socket &socket)
    {
        spdlog::info("EngineServer: Sending message to client");
        try
        {
            boost::asio::write(socket, boost::asio::buffer(msg.getSerializedMsg()));
        }
        catch (const std::exception &e)
        {
            spdlog::error("EngineServer: Exception during sendMessage: {}", e.what());
        }
    }

    Message::Message EngineServer::receiveMessage(boost::asio::ip::tcp::socket &socket)
    {
        try
        {
            boost::asio::streambuf receive_buffer;
            boost::asio::read_until(socket, receive_buffer, Message::TERMINATOR);

            std::istream input(&receive_buffer);
            std::string message;
            std::getline(input, message);

            Message::Message msg;

            try
            {
                msg = MsgHandler::returnCorrectMessageType(message);
            }
            catch (const std::exception &e)
            {
                spdlog::error("EngineServer: Exception during receiveMessage: {}", e.what());
                std::string errorMessage = "Error: " + std::string(e.what());
                std::shared_ptr<Message::MsgInfoIfc> msgInfo = std::make_shared<Message::MsgError>(errorMessage);
                return Message::Message(msgInfo, Message::MsgType::ERROR);
            }

            spdlog::info("EngineServer: Received message from client");

            return msg;
        }
        catch (const std::exception &e)
        {
            spdlog::error("EngineServer: Exception during receiveMessage: {}", e.what());
            std::string errorMessage = "Error: " + std::string(e.what());
            std::shared_ptr<Message::MsgInfoIfc> msgInfo = std::make_shared<Message::MsgError>(errorMessage);
            return Message::Message(msgInfo, Message::MsgType::ERROR);
        }
    }

    void EngineServer::setClientLimit(int limit)
    {
        clientLimit = limit;
    }

    void EngineServer::Stop()
    {
        spdlog::info("EngineServer: EngineServer stopped");
        isRunning_ = false;
        for (auto &session : sessions)
        {
            session->stop();
        }

        for (auto &connection : connections)
        {
            if (connection.joinable())
            {
                connection.join();
            }
            else
            {
                spdlog::error("EngineServer: Connection thread not joinable");
            }
        }
    }

    int EngineServer::getClientLimit()
    {
        return clientLimit;
    }

    bool EngineServer::isRunning()
    {
        return isRunning_;
    }

} // namespace EngineServer