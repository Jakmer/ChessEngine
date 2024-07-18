#include <gtest/gtest.h>

class EngineStarterTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(EngineStarterTest, SampleTest)
{
    ASSERT_EQ(2 + 2, 4);
    ASSERT_EQ(2 + 2, 5);
}

// Main function to run the tests
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}