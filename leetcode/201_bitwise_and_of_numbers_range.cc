// Given two integers left and right that represent the range [left, right],
// return the bitwise AND of all numbers in this range, inclusive.

#include <cmath>
class Solution {
   public:
    int RangeBitwiseAnd(int left, int right) {
        int ret = left;
        for (int i = left + 1; i <= right; i++) {
            ret &= i;
        }
        return ret;
    }

    int RangeBitwiseAndV2(int left, int right) {
        if (left == right) return left;

        int diff = left ^ right;
        int pow = floor(log2(diff));

        return (left >> pow) << pow;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    Solution s;
    int ret = s.RangeBitwiseAnd(5, 7);
    EXPECT_EQ(ret, 4);
}
TEST(t0, t2) {
    Solution s;
    int ret = s.RangeBitwiseAnd(0, 0);
    EXPECT_EQ(ret, 0);
}

TEST(t0, t3) {
    Solution s;
    int left = 1, right = 2147483647;
    int ret = s.RangeBitwiseAndV2(left, right);
    EXPECT_EQ(ret, 0);
}
TEST(t0, t4) {
    Solution s;
    int left = 1, right = 2;
    int ret = s.RangeBitwiseAnd(left, right);
    EXPECT_EQ(ret, 0);
}

#include <benchmark/benchmark.h>

#include <algorithm>
#include <vector>

static void BenchMarkSeqBitAnd(benchmark::State& state) {
    for (auto _ : state) {
        Solution s;
        int left = 1, right = 200000;
        int ret = s.RangeBitwiseAnd(left, right);

        EXPECT_EQ(ret, 0);
    }
}
BENCHMARK(BenchMarkSeqBitAnd);

static void BenchMarkWise(benchmark::State& state) {
    for (auto _ : state) {
        Solution s;
        int left = 1, right = 200000;
        int ret = s.RangeBitwiseAndV2(left, right);

        EXPECT_EQ(ret, 0);
    }
}
BENCHMARK(BenchMarkWise);

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();
    return ret;
}
