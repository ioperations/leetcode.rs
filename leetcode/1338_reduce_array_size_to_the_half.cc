/*You are given an integer array arr. You can choose a set of integers and
remove all the occurrences of these integers in the array.

Return the minimum size of the set so that at least half of the integers of the
array are removed.*/

#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
   public:
    int MinSetSize(vector<int>& arr) {
        int n = arr.size();

        unordered_map<int, int> mp;
        for (auto i : arr) mp[i]++;

        priority_queue<int> pq;
        for (auto& [val, cnt] : mp) pq.push(cnt);

        int val = 0, sum = 0;
        while (!pq.empty() and sum < n / 2) {
            sum += pq.top();
            pq.pop();
            val++;
        }
        return val;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> arr = {3, 3, 3, 3, 5, 5, 5, 2, 2, 7};
    int output = 2;
    /*
    Explanation: Choosing {3,7} will make the new array [5,5,5,2,2] which has
    size 5 (i.e equal to half of the size of the old array). Possible sets of
    size 2 are {3,5},{3,2},{5,2}. Choosing set {2,7} is not possible as it will
    make the new array [3,3,3,3,5,5,5] which has a size greater than half of the
    size of the old array.
    */
    Solution sl;
    int ret = sl.MinSetSize(arr);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> arr = {7, 7, 7, 7, 7, 7};
    int output = 1;
    /*
    The only possible set you can choose is {7}. This will make the new array
    empty.
    */
    Solution sl;
    int ret = sl.MinSetSize(arr);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
