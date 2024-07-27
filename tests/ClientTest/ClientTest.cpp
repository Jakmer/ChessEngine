#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/asio.hpp>
#include "Client.hpp"
#include "EngineServer.hpp"

class ClientTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        io_context_ = std::make_unique<boost::asio::io_context>();
        server_ = std::make_unique<EngineServer::EngineServer>(*io_context_, 12345);

        server_thread_ = std::thread([this]() {
            io_context_->run();
        });

        server_->Start();
    }

    void TearDown() override
    {
        io_context_->stop();
        if (server_thread_.joinable())
        {
            server_thread_.join();
        }
    }

    std::unique_ptr<boost::asio::io_context> io_context_;
    std::unique_ptr<EngineServer::EngineServer> server_;
    std::thread server_thread_;
};

TEST_F(ClientTest, ConnectAndReceiveMessage)
{
    std::string host = "localhost";
    std::string port = "12345";
    Client::Client client(host, port);

    client.connect();

    Message::Message msg("Hello, client!\n");
    server_->sendMessage(msg);

    auto recvMsg = client.receiveMessage();


    EXPECT_EQ(msg.getContent(), recvMsg.getContent());
}

TEST_F(ClientTest, ConnectToNonExistentHost)
{
    std::string host = "nonexistent_host";
    std::string port = "12345";
    Client::Client client(host, port);

    client.connect();

    EXPECT_FALSE(client.isConnected());
}

TEST_F(ClientTest, Disconnect)
{
    std::string host = "localhost";
    std::string port = "12345";
    Client::Client client(host, port);

    client.connect();

    client.disconnect();

    EXPECT_FALSE(client.isConnected());
}

TEST_F(ClientTest, SendMessage)
{
    std::string host = "localhost";
    std::string port = "12345";
    Client::Client client(host, port);

    client.connect();

    std::string message = "Test message";

    Message::Message msg(message);

    client.sendMessage(msg);

    auto recvMsg = server_->receiveMessage();

    EXPECT_EQ(msg.getContent(), recvMsg.getContent());
}