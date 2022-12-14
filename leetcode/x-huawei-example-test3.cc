#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <vector>

/// FIXME: output the result to stdout
void Processing(std::string s) {
    // emit the first 0x
    std::string s2(s.begin() + 2, s.end());

    int ret = 0;

    for (auto& c : s2) {
        int cur = 0;
        if ('A' <= c && c <= 'F') {
            cur = 10 + c - 'A';
        } else if ('a' <= c && c <= 'f') {
            cur = 10 + c - 'a';
        } else if ('0' <= c && c <= '9') {
            cur = c - '0';
        }

        ret = ret * 16 + cur;
    }

    std::cout << ret << std::endl;
}

#if defined(TEST_ADQ)

#include <gtest/gtest.h>

#include <iostream>

TEST(t1, t2) {
    std::string s = "0xA";
    testing::internal::CaptureStdout();
    Processing(s);
    std::string ret = testing::internal::GetCapturedStdout();

    EXPECT_EQ(ret, std::string("10\n"));
}

TEST(t2, t2) {
    std::string s = "0xF";
    testing::internal::CaptureStdout();
    Processing(s);
    std::string ret = testing::internal::GetCapturedStdout();

    EXPECT_EQ(ret, std::string("15\n"));
}

TEST(t3, t1) {
    std::string s = "0xFF";
    testing::internal::CaptureStdout();
    Processing(s);
    std::string ret = testing::internal::GetCapturedStdout();

    EXPECT_EQ(ret, std::string("255\n"));
}

TEST(t0, t2) {
    std::string s = "0xAA";
    testing::internal::CaptureStdout();
    Processing(s);
    std::string ret = testing::internal::GetCapturedStdout();

    EXPECT_EQ(ret, std::string("170\n"));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#else
int main() {
    std::string s;
    while (std::cin >> s) {
        processing(s);
    }
}

#endif
