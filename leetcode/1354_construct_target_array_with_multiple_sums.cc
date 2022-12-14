/*You are given an array target of n integers. From a starting array arr
consisting of n 1's, you may perform the following procedure :

let x be the sum of all elements currently in your array.
choose index i, such that 0 <= i < n and set the value of arr at index i to x.
You may repeat this procedure as many times as needed.
Return true if it is possible to construct the target array from arr, otherwise,
return false.*/

#include <queue>
#include <vector>
using namespace std;

class Solution {
   public:
    bool IsPossible(vector<int>& targets) {
        int n = targets.size();
        long s = 0;
        priority_queue<int, vector<int>> q;
        for (int i = 0; i < n; i++) s += targets[i], q.push(targets[i]);
        while (!q.empty()) {
            int now = q.top();
            q.pop();
            if (now == 1) continue;

            if (s == now || now <= s - now) return 0;
            s -= now;
            now %= s;
            if (s == 1) now = 1;
            q.push(now);
            s += now;
        }
        return 1;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> target = {9, 3, 5};
    bool output = true;
    Solution sl;
    bool ret = sl.IsPossible(target);
    EXPECT_EQ(ret, output);
    // Impossible to create target array from [1,1,1,1].
}

TEST(t0, t2) {
    vector<int> target = {8, 5};
    bool output = true;
    Solution sl;
    bool ret = sl.IsPossible(target);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
