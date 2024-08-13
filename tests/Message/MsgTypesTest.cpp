#include <gtest/gtest.h>
#include "MsgTypes.hpp"
#include <spdlog/spdlog.h>

class MsgTypesTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(MsgTypesTest, MsgPongSerialization) {
    Message::MsgPong msgPong;
    msgPong.serialize();
    std::string serializedData = msgPong.getSerialized();
    ASSERT_FALSE(serializedData.empty()) << "Serialized data should not be empty";
    EXPECT_EQ(serializedData, "9;Pong;01111110");
}

TEST_F(MsgTypesTest, MsgPongDeserialization) {
    std::string serializedString = "9;Pong;01111110";
    Message::MsgPong msgPong(serializedString, true);
    
    EXPECT_EQ(msgPong.type, "9");
    EXPECT_EQ(msgPong.content, "Pong");
}

TEST_F(MsgTypesTest, MsgCommandSerialization) {
    Message::MsgCommand msgCommand("TestCommand");
    msgCommand.serialize();
    std::string serializedData = msgCommand.getSerialized();
    ASSERT_FALSE(serializedData.empty()) << "Serialized data should not be empty";
    EXPECT_EQ(serializedData, "11;TestCommand;;01111110");
}

TEST_F(MsgTypesTest, MsgCommandDeserialization) {
    std::string serializedString = "11;TestCommand;;01111110";
    Message::MsgCommand msgCommand(serializedString, true);

    EXPECT_EQ(msgCommand.type, "11");
    EXPECT_EQ(msgCommand.command, "TestCommand");
    EXPECT_EQ(msgCommand.content, "");
}

TEST_F(MsgTypesTest, MsgConnectSerialization) {
    Message::MsgConnect msgConnect("Wrochess");
    msgConnect.serialize();
    std::string serializedData = msgConnect.getSerialized();
    ASSERT_FALSE(serializedData.empty()) << "Serialized data should not be empty";
    EXPECT_EQ(serializedData, "0;Wrochess;Hello from Wrochess;01111110");
}

TEST_F(MsgTypesTest, MsgConnectDeserialization) {
    std::string serializedString = "0;Wrochess;Hello from Wrochess;01111110";
    Message::MsgConnect msgConnect(serializedString, true);

    EXPECT_EQ(msgConnect.type, "0");
    EXPECT_EQ(msgConnect.name, "Wrochess");
    EXPECT_EQ(msgConnect.content, "Hello from Wrochess");
}