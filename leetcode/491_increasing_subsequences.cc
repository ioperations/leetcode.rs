/*
Given an integer array nums, return all the different possible increasing
subsequences of the given array with at least two elements. You may return the
answer in any order.

The given array may contain duplicates, and two equal integers should also be
considered a special case of increasing sequence.
*/

#include <set>
#include <vector>
using namespace std;

class Solution {
    void Dfs(int i, vector<int>& v, vector<int>& nums, set<vector<int>>& s) {
        if (v.size() >= 2) s.insert(v);
        if (i == (int)nums.size()) return;

        for (int j = i; j < (int)nums.size(); j++) {
            if (v.size() && v.back() > nums[j]) continue;
            v.push_back(nums[j]);
            Dfs(j + 1, v, nums, s);
            v.pop_back();
        }
    }

   public:
    vector<vector<int>> FindSubsequences(vector<int>& nums) {
        set<vector<int>> s;
        vector<int> v;
        Dfs(0, v, nums, s);

        vector<vector<int>> ans(s.begin(), s.end());
        return ans;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> nums = {4, 6, 7, 7};
    vector<vector<int>> output = {{4, 6},    {4, 6, 7}, {4, 6, 7, 7}, {4, 7},
                                  {4, 7, 7}, {6, 7},    {6, 7, 7},    {7, 7}};
    Solution sl;
    auto ret = sl.FindSubsequences(nums);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> nums = {4, 4, 3, 2, 1};
    vector<vector<int>> output = {{4, 4}};

    Solution sl;
    auto ret = sl.FindSubsequences(nums);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
