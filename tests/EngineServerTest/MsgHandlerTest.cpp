#include <gtest/gtest.h>
#include "MsgHandler.hpp"
#include "Message.hpp"

class MsgHandlerUnderTest : public EngineServer::MsgHandler
{
public:
    MsgHandlerUnderTest() : EngineServer::MsgHandler(isRunning) {}
    // Public wrapper for the protected handleConnect method
    Message::Message handleConnectPublic(Message::Message &msg)
    {
        return handleConnect(msg);
    }
private:
    bool isRunning = true;
};

class MsgHandlerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(MsgHandlerTest, Constructor)
{
    std::string name = "Dummy";
    std::shared_ptr<Message::MsgConnect> msgConnect = std::make_shared<Message::MsgConnect>(name);
    Message::Message msg(msgConnect, Message::MsgType::CONNECT);

    EXPECT_NO_THROW(MsgHandlerUnderTest());
}

TEST_F(MsgHandlerTest, HandleMsg)
{
    std::string name = "Dummy";
    std::shared_ptr<Message::MsgConnect> msgConnect = std::make_shared<Message::MsgConnect>(name);
    Message::Message msg(msgConnect, Message::MsgType::CONNECT);

    MsgHandlerUnderTest msgHandler;
    Message::Message response = msgHandler.handleMsg(msg);

    EXPECT_EQ(response.getType(), Message::MsgType::NOTIFICATION);
    EXPECT_EQ(response.getContent(), "true");
}

TEST_F(MsgHandlerTest, ReturnCorrectMessageType)
{
    std::string serializedMsg = "0;Dummy;Hello from Dummy;01111110";
    MsgHandlerUnderTest msgHandler();

    Message::Message msg = EngineServer::MsgHandler::returnCorrectMessageType(serializedMsg);

    EXPECT_EQ(msg.getType(), Message::MsgType::CONNECT);
    EXPECT_EQ(msg.getContent(), "Hello from Dummy");
}

TEST_F(MsgHandlerTest, ReturnCorrectMessageTypeInvalidType)
{
    std::string serializedMsg = "12;Dummy;Hello from Dummy;01111110";
    MsgHandlerUnderTest msgHandler(Message::Message(serializedMsg));

    EXPECT_THROW(EngineServer::MsgHandler::returnCorrectMessageType(serializedMsg), std::invalid_argument);
}

TEST_F(MsgHandlerTest, handleConnectInvalidResponseForHello)
{
    Message::Message msg = Message::Message(std::make_shared<Message::MsgError>("Dummy"), Message::MsgType::CONNECT);
    MsgHandlerUnderTest msgHandler;
    Message::Message response = msgHandler.handleConnectPublic(msg);

    EXPECT_EQ(response.getType(), Message::MsgType::NOTIFICATION);
    EXPECT_EQ(response.getContent(), "false");
}