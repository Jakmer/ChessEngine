#include <gtest/gtest.h>
#include "User.hpp"

class UserTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(UserTest, Constructor)
{
    User::User user("testuser");
    EXPECT_EQ(user.getUsername(), "testuser");
    EXPECT_FALSE(user.getUserID().empty());
}

TEST_F(UserTest, GetUsername)
{
    User::User user("testuser");
    EXPECT_EQ(user.getUsername(), "testuser");
}

TEST_F(UserTest, GetUserID)
{
    User::User user("testuser");
    std::string userID = user.getUserID();
    EXPECT_FALSE(userID.empty());
    EXPECT_EQ(userID.length(), 36);
}

TEST_F(UserTest, UniqueUserID)
{
    User::User user1("user1");
    User::User user2("user2");
    EXPECT_NE(user1.getUserID(), user2.getUserID());
}