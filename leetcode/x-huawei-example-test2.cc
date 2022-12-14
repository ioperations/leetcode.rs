#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

/// FIXME: output the result to stdout
void Processing(std::vector<int>& nums) {
    std::set<int> s(nums.begin(), nums.end());
    std::vector<int> ss(s.begin(), s.end());

    std::sort(ss.begin(), ss.end(), std::less<int>());

    for (auto& s : ss) {
        std::cout << s << std::endl;
    }
}

#if defined(TEST_ADQ)

#include <gtest/gtest.h>

#include <iostream>

TEST(t1, t2) {
    std::vector<int> t{1, 2, 4, 5, 5, 6, 6, 7, 7, 7, 3};
    testing::internal::CaptureStdout();
    Processing(t);
    std::string s = testing::internal::GetCapturedStdout();

    EXPECT_EQ(s, std::string("1\n2\n3\n4\n5\n6\n7\n"));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#else
int main() {
    int n = 0;
    while (std::cin >> n) {
        if (n == 0) {
            return 0;
        }
        std::vector<int> nums{};
        for (int i = 0; i < n; ++i) {
            int tmp;
            std::cin >> tmp;
            nums.push_back(tmp);
        }

        processing(nums);
    }
}

#endif
