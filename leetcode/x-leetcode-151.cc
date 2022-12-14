// reverse words in a string
#include <functional>
#include <iostream>

class Solution {
   public:
    std::string ReverseWords(std::string str) {
        std::function<std::string(std::string)> recursive_fun =
            [&recursive_fun](std::string s) -> std::string {
            std::string ret{};
            if (s.size() == 0) {
                ret = "";
            } else {
                size_t i = 0;
                bool novalue = true;
                for (; i < s.size(); ++i) {
                    if (s[i] == ' ') {
                        if (!novalue) {
                            break;
                        }
                    } else {
                        novalue = false;
                    }
                }

                if (novalue) {
                    return "";
                }

                size_t j = 0;
                // jump the very first space
                for (; j != i; j++) {
                    if (s[j] != ' ') {
                        break;
                    }
                }
                ret = recursive_fun(std::string(s.begin() + i, s.end())) + " " +
                      std::string(s.c_str() + j, s.c_str() + i);
            }
            return ret;
        };
        std::string ret = recursive_fun(str);
        return std::string(ret.begin() + 1, ret.end());
    }
};

#if defined(TEST_ADQ)

#include <gtest/gtest.h>

#include <iostream>

TEST(t1, t2) {
    std::string s(" hello world ");
    Solution slu;
    std::string ret = slu.ReverseWords(s);
    EXPECT_EQ(ret, std::string("world hello"));
}

TEST(t1, t3) {
    std::string s("a good  example");
    Solution slu;
    std::string ret = slu.ReverseWords(s);
    EXPECT_EQ(ret, std::string("example good a"));
}

TEST(t1, t4) {
    std::string s("the sky is blue");
    Solution slu;
    std::string ret = slu.ReverseWords(s);
    EXPECT_EQ(ret, std::string("blue is sky the"));
}
TEST(t1, t5) {
    std::string s(" Bob  Loves Alice ");
    Solution slu;
    std::string ret = slu.ReverseWords(s);
    EXPECT_EQ(ret, std::string("Alice Loves Bob"));
}
TEST(t1, t6) {
    std::string s("Alice does not even like bob");
    Solution slu;
    std::string ret = slu.ReverseWords(s);
    EXPECT_EQ(ret, std::string("bob like even not does Alice"));
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#else

#endif
