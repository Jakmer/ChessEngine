#include <gtest/gtest.h>
#include "MsgHandler.hpp"
#include "Message.hpp"
#include "Session.hpp"
#include "User.hpp"
#include "MockActionHandler.hpp"
#include <memory>
#include <vector>
#include <mutex>
#include <string>



class MsgHandlerUnderTest : public EngineServer::MsgHandler
{
public:
    MsgHandlerUnderTest()
        : EngineServer::MsgHandler(isRunning, users, sessions, mtx, serverName),
          mockActionHandler(std::make_shared<MockActionHandler>(users, sessions, mtx, serverName))
    {
        actionHandler = mockActionHandler;
    }

    std::shared_ptr<MockActionHandler> getMockActionHandler()
    {
        return mockActionHandler;
    }

    // Public wrapper for the protected handleConnect method
    Message::Message handleConnectPublic(Message::Message &msg)
    {
        return handleConnect(msg);
    }

private:
    bool isRunning = true;
    std::vector<std::shared_ptr<User::User>> users;
    std::vector<std::shared_ptr<Session::Session>> sessions;
    std::mutex mtx;
    std::string serverName;
    std::shared_ptr<MockActionHandler> mockActionHandler;
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
    MsgHandlerUnderTest msgHandler;

    Message::Message msg = EngineServer::MsgHandler::returnCorrectMessageType(serializedMsg);

    EXPECT_EQ(msg.getType(), Message::MsgType::CONNECT);
    EXPECT_EQ(msg.getContent(), "Hello from Dummy");
}

TEST_F(MsgHandlerTest, ReturnCorrectMessageTypeInvalidType)
{
    std::string serializedMsg = "12;Dummy;Hello from Dummy;01111110";
    MsgHandlerUnderTest msgHandler;

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

TEST_F(MsgHandlerTest, handleNotificationDialogChoice0_1)
{
    std::string notification = "Dialog choice 0";
    std::string content = "1";
    std::shared_ptr<Message::MsgNotification> msgNotification = std::make_shared<Message::MsgNotification>(notification, content);
    Message::Message msg(msgNotification, Message::MsgType::NOTIFICATION);

    MsgHandlerUnderTest msgHandler;
    auto mockActionHandler = msgHandler.getMockActionHandler();

    EXPECT_CALL(*mockActionHandler, joinGame()).Times(1);

    auto user = std::make_shared<User::User>("Dummy");
    msgHandler.setUser(user);
    Message::Message response = msgHandler.handleMsg(msg);

    //EXPECT_EQ(response.getType(), Message::MsgType::NOTIFICATION);
    //EXPECT_EQ(response.getContent(), "true");
}

TEST_F(MsgHandlerTest, handleNotificationDialogChoice0_2)
{
    std::string notification = "Dialog choice 0";
    std::string content = "2";
    std::shared_ptr<Message::MsgNotification> msgNotification = std::make_shared<Message::MsgNotification>(notification, content);
    Message::Message msg(msgNotification, Message::MsgType::NOTIFICATION);

    MsgHandlerUnderTest msgHandler;
    auto mockActionHandler = msgHandler.getMockActionHandler();

    EXPECT_CALL(*mockActionHandler, createGame()).Times(1);

    auto user = std::make_shared<User::User>("Dummy");
    msgHandler.setUser(user);
    Message::Message response = msgHandler.handleMsg(msg);

    //EXPECT_EQ(response.getType(), Message::MsgType::NOTIFICATION);
    //EXPECT_EQ(response.getContent(), "true");
}

TEST_F(MsgHandlerTest, handleNotificationDialogChoice0_3)
{
    std::string notification = "Dialog choice 0";
    std::string content = "3";
    std::shared_ptr<Message::MsgNotification> msgNotification = std::make_shared<Message::MsgNotification>(notification, content);
    Message::Message msg(msgNotification, Message::MsgType::NOTIFICATION);

    MsgHandlerUnderTest msgHandler;
    auto mockActionHandler = msgHandler.getMockActionHandler();

    EXPECT_CALL(*mockActionHandler, userExit()).Times(1);

    auto user = std::make_shared<User::User>("Dummy");
    msgHandler.setUser(user);
    Message::Message response = msgHandler.handleMsg(msg);

    //EXPECT_EQ(response.getType(), Message::MsgType::NOTIFICATION);
    //EXPECT_EQ(response.getContent(), "true");
}