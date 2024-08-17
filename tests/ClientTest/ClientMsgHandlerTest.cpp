#include <gtest/gtest.h>
#include "MsgHandler.hpp"
#include "Message.hpp"
#include "Client.hpp"

class ClientMsgHandlerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(ClientMsgHandlerTest, Constructor)
{
    EXPECT_NO_THROW(Client::MsgHandler());
}

TEST_F(ClientMsgHandlerTest, handleMsgConnect)
{
    Client::MsgHandler msgHandler;
    std::string serverName = "Dummy";
    Message::Message msg = Message::Message(std::make_shared<Message::MsgConnect>(serverName), Message::MsgType::CONNECT);
    auto result = msgHandler.handleMsg(msg);
    //EXPECT_EQ(result.getType(), Message::MsgType::CONNECT);
    //EXPECT_EQ(result.getContent(), "Hello from " + serverName);
}
