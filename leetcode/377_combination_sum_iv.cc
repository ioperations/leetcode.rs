/*
Given an array of distinct integers nums and a target integer target, return the
number of possible combinations that add up to target.

The test cases are generated so that the answer can fit in a 32-bit integer.
*/

#include <vector>
using namespace std;
class Solution {
   private:
    int Combination(vector<int>& nums, int target, vector<int>& dp) {
        if (target == 0) return 1;
        if (target < 0) return 0;

        if (dp[target] != -1) return dp[target];
        int ans = 0;
        for (int i = 0; i < (int)nums.size(); i++) {
            ans += Combination(nums, target - nums[i], dp);
        }

        return dp[target] = ans;
    }

   public:
    int CombinationSum4(vector<int>& nums, int target) {
        vector<int> dp(1001, -1);
        return Combination(nums, target, dp);
    }
    int ans = 0;

    int CombinationSum4V1(vector<int>& nums, int tar) {
        if (nums.size() == 0) return 0;

        vector<unsigned int> dp(tar + 1, 0);
        dp[0] = 1;

        for (int i = 1; i < tar + 1; i++) {
            for (auto num : nums) {
                if (i - num >= 0) dp[i] = dp[i] + dp[i - num];
            }
        }
        // DP Approach
        return dp[tar];

        // BackTracking
    }

   public:
    int CombinationSum4V2(vector<int>& nums, int tar) {
        return Backtrack(nums, tar, 0);
    }

   private:
    int Backtrack(vector<int> nums, int tar, int index) {
        if (index >= (int)nums.size()) return 0;
        if (tar == 0) return 1;

        int ans = 0;

        for (int i = 0; i < (int)nums.size(); i++) {
            if (tar - nums[i] >= 0) {
                tar -= nums[i];

                ans += Backtrack(nums, tar, i);

                tar += nums[i];
            }
        }

        return ans;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> nums = {1, 2, 3};
    int target = 4;
    Solution sl;
    /*
        The possible combination ways are:
        (1, 1, 1, 1)
        (1, 1, 2)
        (1, 2, 1)
        (1, 3)
        (2, 1, 1)
        (2, 2)
        (3, 1)
        Note that different sequences are counted as different combinations.
    */

    int ret = sl.CombinationSum4(nums, target);
    EXPECT_EQ(ret, 7);
}

TEST(t0, t2) {
    vector<int> nums = {9};
    int target = 3;
    Solution sl;

    int ret = sl.CombinationSum4(nums, target);
    EXPECT_EQ(ret, 0);
}

TEST(t1, t1) {
    vector<int> nums = {1, 2, 3};
    int target = 4;
    Solution sl;
    /*
        The possible combination ways are:
        (1, 1, 1, 1)
        (1, 1, 2)
        (1, 2, 1)
        (1, 3)
        (2, 1, 1)
        (2, 2)
        (3, 1)
        Note that different sequences are counted as different combinations.
    */

    int ret = sl.CombinationSum4V1(nums, target);
    EXPECT_EQ(ret, 7);
}

TEST(t1, t2) {
    vector<int> nums = {9};
    int target = 3;
    Solution sl;

    int ret = sl.CombinationSum4V1(nums, target);
    EXPECT_EQ(ret, 0);
}

TEST(t2, t1) {
    vector<int> nums = {1, 2, 3};
    int target = 4;
    Solution sl;
    /*
        The possible combination ways are:
        (1, 1, 1, 1)
        (1, 1, 2)
        (1, 2, 1)
        (1, 3)
        (2, 1, 1)
        (2, 2)
        (3, 1)
        Note that different sequences are counted as different combinations.
    */

    int ret = sl.CombinationSum4V2(nums, target);
    EXPECT_EQ(ret, 7);
}

TEST(t2, t2) {
    vector<int> nums = {9};
    int target = 3;
    Solution sl;

    int ret = sl.CombinationSum4V2(nums, target);
    EXPECT_EQ(ret, 0);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
