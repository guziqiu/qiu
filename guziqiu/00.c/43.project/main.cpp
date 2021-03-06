#include <stdio.h>
#include <gtest/gtest.h>

int add(int a, int b) {
    return a + b;
}

TEST(func, add) {
    EXPECT_EQ(add(1, 2), 3);
    EXPECT_EQ(add(2, 4), 7);
    EXPECT_EQ(add(2, 4), 6);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

