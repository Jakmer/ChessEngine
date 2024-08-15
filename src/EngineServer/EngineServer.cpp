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
                                                                                 mtx(),
                                                                                 serverName("Wrochess")
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

    bool EngineServer::validateConnection(const Message::Message &msg)
    {
        return msg.getType() == Message::MsgType::NOTIFICATION && msg.getContent() == "true";
    }

    void EngineServer::handleConnection(boost::asio::ip::tcp::socket socket)
    {
        spdlog::info("EngineServer: Connection accepted");

        bool isRunning = true;
        MsgCreator msgCreator;
        MsgHandler msgHandler(isRunning);

        // TODO: implement timeout for receiving message

        auto clientHelloMsg = receiveMessage(socket);
        if(clientHelloMsg.getType() != Message::MsgType::CONNECT)
        {
            spdlog::error("EngineServer: Expected CONNECT message, but received different message");
            auto respond = Message::Message(msgCreator.msgError("No client hello"), Message::MsgType::ERROR);
            sendMessage(respond, socket);
            return;
        }

        auto clientHelloValidation = msgHandler.handleMsg(clientHelloMsg);
        if (!validateConnection(clientHelloValidation))
        {
            spdlog::error("EngineServer: Connection failed: No client hello");
            auto respond = Message::Message(msgCreator.msgError("No client hello"), Message::MsgType::ERROR);
            sendMessage(respond, socket);
            return;
        }

        auto connectMsgInfo = msgCreator.msgConnect(serverName);
        auto connectMsg = Message::Message(connectMsgInfo, Message::MsgType::CONNECT);
        sendMessage(connectMsg, socket);
        spdlog::info("EngineServer: Connection successful");

        Message::MsgConnect clientMsg = Message::MsgConnect(clientHelloMsg.getSerializedMsg(), true);
        auto username = clientMsg.name;
        auto user = std::make_shared<User::User>(username);

        while(isRunning)
        {
            auto msg = receiveMessage(socket);
            auto response = msgHandler.handleMsg(msg);
            break;
            sendMessage(response, socket);
            // consider makeing msgHandler as friend class so it can access private members
        }

        //auto session = std::make_shared<Session::Session>(std::move(socket));
        // For the future all action handling should be done by msgHandler and here only messages should be sent and received
        mtx.lock();
        users.push_back(user);
        // sessions.push_back(session);
        mtx.unlock();



        // TODO: send message to client to open dialog for choosing existing game or creating new game

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