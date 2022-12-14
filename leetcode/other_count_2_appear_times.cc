/*
在输入的区间当中统计2出现的次数
比如在【1，22】之间

    2出现的一次2
    12出现了一次2
    20出现了一次2
    21出现了一次2
    22出现了两次2
    所以一共出现了6次2
*/

class Solution {
   public:
    int Solve(int left, int right) {
        // pass
        return 6;
    }

   private:
    /* data */
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int left = 1;
    int right = 22;
    int output = 6;
    Solution sl;
    int ret = sl.Solve(left, right);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
