#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include "EngineServer.hpp"

class EngineServerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(EngineServerTest, StartWithProperParameters)
{
    boost::asio::io_context ioContext;
    short port = 8080;

    EXPECT_NO_THROW(EngineServer::EngineServer engineServer(ioContext, port));
}

TEST_F(EngineServerTest, StartWithWrongParameters)
{
    boost::asio::io_context ioContext;
    short port = -1;

    EXPECT_THROW(EngineServer::EngineServer engineServer(ioContext, port), std::exception);
}

TEST_F(EngineServerTest, StartWithBusyPort)
{
    boost::asio::io_context ioContext;
    short port = 8080;

    EngineServer::EngineServer engineServer(ioContext, port);

    EXPECT_THROW(EngineServer::EngineServer engineServer2(ioContext, port), std::exception);
}

