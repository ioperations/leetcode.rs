/*Given a sorted integer array arr, two integers k and x, return the k closest
integers to x in the array. The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b*/
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> FindClosestElements(vector<int>& arr, int k, int x) {
        vector<int>::iterator const iter =
            lower_bound(arr.begin(), arr.end(), x);
        int j = iter - arr.begin();
        int i = j - 1;
        vector<int> ans;
        int const n = arr.size();

        while (i >= 0 && j < n && (int)ans.size() < k) {
            if (abs(x - arr[i]) <= abs(x - arr[j])) {
                ans.push_back(arr[i]);
                i--;
            } else {
                ans.push_back(arr[j]);
                j++;
            }
        }

        while (i >= 0 && ans.size() < k) {
            ans.push_back(arr[i]);
            i--;
        }

        while (j < n && (int)ans.size() < k) {
            ans.push_back(arr[j]);
            j++;
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> arr = {1, 2, 3, 4, 5};
    int const k = 4, x = 3;
    vector<int> const output = {1, 2, 3, 4};
    Solution sl;
    auto ret = sl.FindClosestElements(arr, k, x);
    EXPECT_EQ(ret, output);
};

TEST(t0, t2) {
    vector<int> arr = {1, 2, 3, 4, 5};
    int const k = 4, x = -1;
    vector<int> const output = {1, 2, 3, 4};
    Solution sl;
    auto ret = sl.FindClosestElements(arr, k, x);
    EXPECT_EQ(ret, output);
};
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
