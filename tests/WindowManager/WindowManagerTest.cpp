#include <gtest/gtest.h>
#include <sstream>
#include "WindowManager.hpp"

class WindowManagerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(WindowManagerTest, Constructor)
{
    EXPECT_NO_THROW(WindowManager::WindowManager());
}

TEST_F(WindowManagerTest, showDialogAndAwaitResponse)
{
    WindowManager::WindowManager wm;

    std::istringstream input("2\n");
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    int result = wm.showDialogAndAwaitResponse();

    std::cout.rdbuf(oldCoutStreamBuf);

    EXPECT_EQ(result, 2);
    EXPECT_NE(output.str().find("Please choose an option:"), std::string::npos);
    EXPECT_NE(output.str().find("1. Join game"), std::string::npos);
    EXPECT_NE(output.str().find("2. Create new game"), std::string::npos);
    EXPECT_NE(output.str().find("3. Exit"), std::string::npos);
}
