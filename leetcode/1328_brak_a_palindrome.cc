/*Given a palindromic string of lowercase English letters palindrome, replace
exactly one character with any lowercase English letter so that the resulting
string is not a palindrome and that it is the lexicographically smallest one
possible.

Return the resulting string. If there is no way to replace a character to make
it not a palindrome, return an empty string.

A string a is lexicographically smaller than a string b (of the same length) if
in the first position where a and b differ, a has a character strictly smaller
than the corresponding character in b. For example, "abcc" is lexicographically
smaller than "abcd" because the first position they differ is at the fourth
character, and 'c' is smaller than 'd'.

*/

#include <string>
#include <unordered_map>
using namespace std;

class Solution {
   public:
    string BreakPalindrome(string palindrome) {
        string& ret = palindrome;
        int const original_size = palindrome.size();
        int const size = palindrome.size() / 2;
        for (int i = 0; i < size; i++) {
            if (ret[i] != 'a') {
                ret[i] = 'a';
                return ret;
            }
        }
        if (original_size > 1) {
            for (int i = 0; i < size; i++) {
                if (ret[i] == 'a') {
                    ret[original_size - (i + 1)] = 'b';
                    return ret;
                }
            }
        }
        return "";
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string const palindrome = "abccba";
    string const output = "aaccba";
    // Explanation: There are many ways to make "abccba" not a palindrome, such
    // as "zbccba", "aaccba", and "abacba". Of all the ways, "aaccba" is the
    // lexicographically smallest.
    Solution sl;
    auto const ret = sl.BreakPalindrome(palindrome);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string const palindrome = "a";
    string const output = "";
    // There is no way to replace a single character to make "a" not a
    // palindrome, so return an empty string.
    Solution sl;
    auto const ret = sl.BreakPalindrome(palindrome);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    string const palindrome = "aa";
    string const output = "ab";
    // There is no way to replace a single character to make "a" not a
    // palindrome, so return an empty string.
    Solution sl;
    auto const ret = sl.BreakPalindrome(palindrome);
    EXPECT_EQ(ret, output);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
