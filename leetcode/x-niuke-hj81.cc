#include <algorithm>
#include <iostream>
#include <map>

void Func(std::string& less, std::string& more) {
    bool t = true;
    std::map<int, char> less_set{};
    for (size_t i = 0; i < less.size(); ++i) {
        less_set.emplace(i, less[i]);
    }

    for (size_t i = 0; i < less_set.size(); ++i) {
        auto z = std::find_if(
            more.begin(), more.end(),
            [&less_set, &i](const char& c) { return c == less_set[i]; });
        if (z == std::end(more)) {
            t = false;
            break;
        }
    }

    std::cout << (t ? "true" : "false") << std::endl;
}

#if defined(TEST_ADQ)
#include <gtest/gtest.h>

#include <iostream>

TEST(t1, t2) {
    testing::internal::CaptureStdout();
    std::string le("bc");
    std::string more("abc");
    Func(le, more);
    std::string out = testing::internal::GetCapturedStdout();
    std::string expected = "true\n";
    EXPECT_EQ(out, expected);
}

TEST(t1, t3) {
    testing::internal::CaptureStdout();
    std::string le("bd");
    std::string more("abc");
    Func(le, more);
    std::string out = testing::internal::GetCapturedStdout();
    std::string expected = "false\n";
    EXPECT_EQ(out, expected);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#else

int main() {
    std::string less{};
    std::string more{};
    while (std::cin >> less >> more) {
        Func(less, more);
    }

    return 0;
}

#endif
