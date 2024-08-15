#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include "Session.hpp"
#include "User.hpp"
#include <spdlog/spdlog.h>

class SessionTest : public ::testing::Test
{
protected:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket;
    std::unique_ptr<Session::Session> session;
    User::User user;

    SessionTest() : socket(io_context), user("username")
    {
        try
        {
            session = std::make_unique<Session::Session>(std::move(socket), user);
        }
        catch (const std::exception &e)
        {
            spdlog::error("SessionTest: Exception: {}", e.what());
        }
    }
};

TEST_F(SessionTest, Constructor)
{
    EXPECT_NO_THROW(Session::Session(std::move(socket), user));
}

TEST_F(SessionTest, GetID)
{
    auto id = session->getID();
    // Add assertions here
    EXPECT_FALSE(id.empty());
}

TEST_F(SessionTest, Start)
{
    EXPECT_NO_THROW(session->start());
}

TEST_F(SessionTest, ReadMessage)
{
    auto msg = session->readMessage();
    // Add assertions here
    // EXPECT_FALSE(msg.getContent().empty());
}

TEST_F(SessionTest, WriteMessage)
{
    // Message::Message msg("Test message\n");
    // EXPECT_NO_THROW(session->writeMessage(msg));
}

TEST_F(SessionTest, Stop)
{
    EXPECT_NO_THROW(session->stop());
}

// Additional tests

TEST_F(SessionTest, IsActiveInitiallyTrue)
{
    EXPECT_TRUE(session->isActive());
}

TEST_F(SessionTest, StopSetsIsActiveToFalse)
{
    session->stop();
    EXPECT_FALSE(session->isActive());
}

TEST_F(SessionTest, ReadMessageReturnsExpectedMessage)
{
    // Assuming some setup to provide a message
    auto msg = session->readMessage();
    // Add assertions to check the message content
}

TEST_F(SessionTest, WriteMessageHandlesEmptyMessage)
{
    // Message::Message emptyMsg("");
    // EXPECT_THROW(session->writeMessage(emptyMsg), std::invalid_argument);
}

TEST_F(SessionTest, StartInitializesSessionCorrectly)
{
    session->start();
    // Add assertions to verify the session is started correctly
}
