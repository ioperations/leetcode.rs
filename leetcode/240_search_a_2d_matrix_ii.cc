/*Write an efficient algorithm that searches for a value target in an m x n
integer matrix matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
*/

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    bool Binarys(vector<int>& row, int target) {
        int l = 0, r = row.size();
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (row[mid] == target) return true;
            if (row[mid] > target)
                r = mid;
            else
                l = mid + 1;
        }
        return false;
    }

    bool SearchMatrix(vector<vector<int>>& matrix, int target) {
        int i = 0;
        int j = matrix[0].size() - 1;

        while (j >= 0 && i < (int)matrix.size()) {
            // If it matches it will return true
            if (matrix[i][j] == target) {
                return true;
            }

            // if we find value is greater than we go to left side
            if (matrix[i][j] > target) {
                j--;
            }

            //  value is smaller so go to bottom side
            else {
                i++;
            }
        }

        return false;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<vector<int>> matrix = {{1, 4, 7, 11, 15},
                                  {2, 5, 8, 12, 19},
                                  {3, 6, 9, 16, 22},
                                  {10, 13, 14, 17, 24},
                                  {18, 21, 23, 26, 30}};
    int target = 5;
    bool output = true;

    Solution sl;
    bool ret = sl.SearchMatrix(matrix, target);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<vector<int>> matrix = {{1, 4, 7, 11, 15},
                                  {2, 5, 8, 12, 19},
                                  {3, 6, 9, 16, 22},
                                  {10, 13, 14, 17, 24},
                                  {18, 21, 23, 26, 30}};
    int target = 20;
    bool output = false;

    Solution sl;
    bool ret = sl.SearchMatrix(matrix, target);
    EXPECT_EQ(ret, output);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
