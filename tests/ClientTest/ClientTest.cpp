#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/asio.hpp>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "Client.hpp"
#include "EngineServer.hpp"
#include "MsgTypes.hpp"
#include <memory>

class ClientTest : public ::testing::Test
{
protected:
    pid_t serverPid = -1;

    void TearDown() override
    {
        if (serverPid > 0)
        {
            kill(serverPid, SIGTERM);
            waitpid(serverPid, nullptr, 0);
        }
    }
};

TEST_F(ClientTest, ConnectAndReceiveMessage)
{
    serverPid = fork();
    if (serverPid == 0)
    {
        boost::asio::io_context io_context;
        EngineServer::EngineServer server(io_context, 12345);
        server.setClientLimit(1);
        server.Start();
        io_context.run();
        exit(0);
    }
    else if (serverPid < 0)
    {
        FAIL() << "Failed to fork process for server";
    }
    sleep(1);

    std::string host = "localhost";
    std::string port = "12345";
    Client::Client client(host, port);

    client.connect();

    std::shared_ptr<Message::MsgInfoIfc> clientHello = std::make_shared<Message::MsgConnect>("Client");
    auto msg = Message::Message(clientHello, Message::MsgType::CONNECT);
    client.sendMessage(msg);
    auto recvMsg = client.receiveMessage();
    std::shared_ptr<Message::MsgConnect> msgConnect = std::make_shared<Message::MsgConnect>(recvMsg.getSerializedMsg(), true);

    EXPECT_EQ("Hello from Wrochess", msgConnect->content);
    EXPECT_EQ(Message::MsgType::CONNECT, msg.getType());
    EXPECT_EQ("Wrochess", msgConnect->name);
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
    serverPid = fork();
    if (serverPid == 0)
    {
        boost::asio::io_context io_context;
        EngineServer::EngineServer server(io_context, 12345);
        server.setClientLimit(1);
        server.Start();
        io_context.run();
        exit(0);
    }
    else if (serverPid < 0)
    {
        FAIL() << "Failed to fork process for server";
    }
    sleep(1); // Poczekaj chwilę, aby serwer się uruchomił

    std::string host = "localhost";
    std::string port = "12345";
    Client::Client client(host, port);

    client.connect();

    client.disconnect();

    EXPECT_FALSE(client.isConnected());
}
