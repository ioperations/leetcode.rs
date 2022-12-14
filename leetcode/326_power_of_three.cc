/*
Given an integer n, return true if it is a power of three.Otherwise,
    return false.

    An integer n is a power of three,
    if there exists an integer x such that n == 3x.
*/

class Solution {
   public:
    bool IsPowerOfThree(int n) {
        if (n == 0) {
            return false;
        }
        if (n % 3 == 0) {
            return true;
        }
        return false;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int n = 27;
    bool expected = true;

    Solution sl;
    bool ret = sl.IsPowerOfThree(n);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    int n = 0;
    bool expected = false;

    Solution sl;
    bool ret = sl.IsPowerOfThree(n);
    EXPECT_EQ(ret, expected);
}
TEST(t0, t3) {
    int n = 9;
    bool expected = true;

    Solution sl;
    bool ret = sl.IsPowerOfThree(n);
    EXPECT_EQ(ret, expected);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
