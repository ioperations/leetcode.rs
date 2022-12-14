#include <vector>

using namespace std;
class Solution {
   public:
    vector<vector<int>> GenerateMatrix(int n) {
        /*
         _______ _______ _______
        |       |       |       |
        |   1 --|-> 2 --|-> 3   |
        |       |       |   |   |
        |_______|_______|___|___|
        |       |       |   `   |
        |   8 --|-> 9   |   4   |
        |   ^   |       |   |   |
        |___|___|_______|___|___|
        |   |   |       |   *   |
        |   7 <-|-- 6 <-|-- 5   |
        |       |       |       |
        |_______|_______|_______|
        */

        vector<vector<int>> ret;
        ret.resize(n);
        for (auto& ptr : ret) {
            ptr.resize(n);
        }
        enum direction {
            right,
            down,
            left,
            up,
        };

        direction direction = right;

        int i = 0, j = 0;
        for (int count = 1; count <= n * n;) {
            switch (direction) {
                case right: {
                    if (j >= n) {
                        direction = down;
                        j = n - 1;
                        i++;
                        break;
                    }
                    if (ret[i][j]) {
                        direction = down;
                        j--;
                        i++;
                        break;
                    }

                    ret[i][j] = count;
                    count++;
                    j++;
                    break;
                }
                case down: {
                    if (i >= n) {
                        direction = left;
                        i = n - 1;
                        j--;
                        break;
                    }

                    if (ret[i][j]) {
                        direction = left;
                        i--;
                        j--;
                        break;
                    }
                    ret[i][j] = count;
                    count++;
                    i++;
                    break;
                }
                case left: {
                    if (j < 0) {
                        direction = up;
                        j = 0;
                        i--;
                        break;
                    }

                    if (ret[i][j]) {
                        direction = up;
                        j++;
                        i--;
                        break;
                    }
                    ret[i][j] = count;
                    j--;
                    count++;
                    break;
                }
                case up: {
                    if (i < 0) {
                        direction = right;
                        i = 0;
                        j++;
                        break;
                    }

                    if (ret[i][j]) {
                        direction = right;
                        i++;
                        j++;
                        break;
                    }
                    ret[i][j] = count;
                    count++;
                    i--;

                    break;
                }
            }
        }

        return ret;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t0) {
    int n = 3;

    std::vector<std::vector<int>> expected = {{1, 2, 3}, {8, 9, 4}, {7, 6, 5}};
    Solution s;
    auto ret = s.GenerateMatrix(n);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t1) {
    int n = 1;
    std::vector<std::vector<int>> expected = {{1}};
    Solution s;
    auto ret = s.GenerateMatrix(n);
    EXPECT_EQ(ret, expected);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
