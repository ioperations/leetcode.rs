/*
Given a string s, find the longest palindromic subsequence's length in s.

A subsequence is a sequence that can be derived from another sequence by
deleting some or no elements without changing the order of the remaining
elements.
*/
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int Lcs(string string1, string string2) {
        int n1 = string1.length();
        int n2 = string2.length();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                if (string1[i] == string2[j])
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                else
                    dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
        return dp[n1][n2];
    }
    int LongestPalindromeSubseq(string s) {
        string k = s;
        reverse(s.begin(), s.end());
        return Lcs(s, k);
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string s = "bbbab";
    int output = 4;
    // Explanation: One possible longest palindromic subsequence is "bbbb".
    Solution sl;
    int ret = sl.LongestPalindromeSubseq(s);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string s = "cbbd";
    int output = 2;
    // One possible longest palindromic subsequence is "bb".
    Solution sl;
    int ret = sl.LongestPalindromeSubseq(s);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
