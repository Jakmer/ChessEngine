#include <gtest/gtest.h>
#include <memory>
#include "Message.hpp"
#include "MsgTypes.hpp"
#include "MsgInfoIfc.hpp"

class MessageTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Setup code if needed
    }

    void TearDown() override
    {
        // Cleanup code if needed
    }
};

TEST_F(MessageTest, GetMessageType)
{
    std::string name = "Dummy";
    std::shared_ptr<Message::MsgConnect> msgConnect = std::make_shared<Message::MsgConnect>(name);
    Message::Message msg(msgConnect, Message::MsgType::CONNECT);

    EXPECT_EQ(msg.getType(), Message::MsgType::CONNECT);
}

TEST_F(MessageTest, GetSerializedMessage)
{
    std::string name = "Dummy";
    std::shared_ptr<Message::MsgConnect> msgConnect = std::make_shared<Message::MsgConnect>(name);
    Message::Message msg(msgConnect, Message::MsgType::CONNECT);

    EXPECT_EQ(msg.getSerializedMsg(), "0;Dummy;Hello from Dummy;01111110");
}

TEST_F(MessageTest, EmptyMessage)
{
    std::string name = "Dummy";
    std::shared_ptr<Message::MsgConnect> msgConnect = std::make_shared<Message::MsgConnect>(name);
    Message::Message msg(msgConnect, Message::MsgType::CONNECT);

    EXPECT_FALSE(msg.empty());
}


TEST_F(MessageTest, GetContent)
{
    std::string name = "Dummy";
    std::shared_ptr<Message::MsgConnect> msgConnect = std::make_shared<Message::MsgConnect>(name);
    Message::Message msg(msgConnect, Message::MsgType::CONNECT);

    EXPECT_EQ(msg.getContent(), "Hello from "+name);
}