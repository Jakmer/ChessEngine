#include <gtest/gtest.h>
#include "Message.hpp"
#include "MsgTypes.hpp"

class MessageTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

// TODO: Implement tests for Message class

TEST_F(MessageTest, ConstructorLValue)
{
    std::string msg = "Hello, World!";
   // Message::Message message(msg);
   // EXPECT_EQ(message.getContent(), msg);
}

TEST_F(MessageTest, ConstructorRValue)
{
    std::string msg = "Hello, World!";
    //Message::Message message(std::move(msg));
    //EXPECT_EQ(message.getContent(), "Hello, World!");
}

TEST_F(MessageTest, GetContent)
{
    std::string msg = "Test Content";
    //Message::Message message(msg);
    //EXPECT_EQ(message.getContent(), msg);
}

TEST_F(MessageTest, Serialize)
{
    std::string msg = "Serialize Test";
    //Message::Message message(msg);
    //message.serialize();
    // EXPECT_EQ(message.getContent(), expectedSerializedContent);
}

TEST_F(MessageTest, Deserialize)
{
    std::string msg = "Deserialize Test";
    //Message::Message message(msg);
    //message.deserialize();
    // EXPECT_EQ(message.getContent(), expectedDeserializedContent);
}