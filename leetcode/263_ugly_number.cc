/*An ugly number is a positive integer whose prime factors are limited to 2, 3,
and 5. Given an integer n, return true if n is an ugly number.*/

#include <unordered_map>
using namespace std;

class Solution {
    std::unordered_map<int, bool> cache;

   public:
    bool IsUgly(int n) {
        if (n == 0) return false;
        if (n == 1) return true;
        if (cache.count(n)) return cache[n];

        int t2 = n / 2;
        int t_2 = n % 2;
        if (t_2 == 0 && IsUgly(t2)) {
            cache[n] = true;
            return true;
        }
        int t3 = n / 3;
        int t_3 = n % 3;
        if (t_3 == 0 && IsUgly(t3)) {
            cache[n] = true;
            return true;
        }

        int t4 = n / 5;
        int t_4 = n % 5;
        if (t_4 == 0 && IsUgly(t4)) {
            cache[n] = true;
            return true;
        }

        cache[n] = false;
        return false;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int n = 6;
    bool output = true;
    // Explanation: 6 = 2 × 3
    Solution sl;
    bool ret = sl.IsUgly(n);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    int n = 1;
    bool output = true;
    // 1 has no prime factors, therefore all of its prime factors are limited to
    // 2, 3, and 5.
    Solution sl;
    bool ret = sl.IsUgly(n);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    int n = 14;
    bool output = false;
    // 14 is not ugly since it includes the prime factor 7.
    Solution sl;
    bool ret = sl.IsUgly(n);
    EXPECT_EQ(ret, output);
}

TEST(t0, t4) {
    int n = 0;
    bool output = false;
    // 14 is not ugly since it includes the prime factor 7.
    Solution sl;
    bool ret = sl.IsUgly(n);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
