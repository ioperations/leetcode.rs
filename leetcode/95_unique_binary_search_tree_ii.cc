/*Given an integer n, return all the structurally unique BST's (binary search
   trees), which has exactly n nodes of unique values from 1 to n. Return the
   answer in any order.

 */

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};
#include <functional>
#include <map>
#include <set>
#include <vector>
using namespace std;
class Solution {
   public:
    vector<TreeNode*> GenerateTrees(int n) { return SubTrees(1, n); }

   private:
    vector<TreeNode*> SubTrees(int start, int end) {
        vector<TreeNode*> res;
        if (start > end) {
            res.push_back(NULL);
            return res;
        }
        for (int i = start; i <= end; i++) {
            vector<TreeNode*> left = SubTrees(start, i - 1);
            vector<TreeNode*> right = SubTrees(i + 1, end);
            for (TreeNode* l : left) {
                for (TreeNode* r : right) {
                    TreeNode* root = new TreeNode(i);
                    root->left = l;
                    root->right = r;
                    res.push_back(root);
                }
            }
        }
        return res;
    }
    vector<TreeNode*> GenerateTreesV2(int n) {
        vector<TreeNode*> ret;
        map<int, int> cache;
        function<vector<TreeNode*>(int, vector<int>&)> fun =
            [&](int j, vector<int>& ele) -> vector<TreeNode*> {
            vector<TreeNode*> ret;
            if (j == 0) {
                ret.push_back(nullptr);
                return ret;
            }
            if (j == 1) {
                ret.push_back(new TreeNode(ele[0]));
                return ret;
            }
            if (j == 2) {
                TreeNode* n1 = new TreeNode(ele[0]);
                n1->right = new TreeNode(ele[1]);

                ret.push_back(n1);

                n1 = new TreeNode(ele[1]);
                n1->left = new TreeNode(ele[0]);
                ret.push_back(n1);

                return ret;
            }

            for (int i = 0; i < j; i++) {
                // fun(j - i - 1);
                // fun(i);
            }
            return ret;
        };
        // fun(n);

        return ret;
    }
};

#include <gtest/gtest.h>

#include <functional>
#include <iostream>
#include <queue>

std::vector<vector<optional<int>>> Flattern(vector<TreeNode*>& vec) {
    std::vector<vector<optional<int>>> ret;
    auto fun = [](TreeNode* root) -> std::vector<optional<int>> {
        std::vector<optional<int>> ret;

        if (root == nullptr) {
            return ret;
        }
        queue<TreeNode*> q;
        q.push(root);

        while (q.size()) {
            TreeNode* tmp = q.front();
            if (tmp) {
                ret.push_back(tmp->val);
                q.push(tmp->left);
                q.push(tmp->right);
            } else {
                ret.push_back(optional<int>());
            }
            q.pop();
        }
        while (true) {
            if (!ret.back().has_value())
                ret.pop_back();
            else {
                break;
            }
        }
        return ret;
    };

    for (auto& ptr : vec) {
        ret.push_back(fun(ptr));
    }

    return ret;
}

void FreeNodes(TreeNode* root) {
    if (root == nullptr) return;
    FreeNodes(root->left);
    FreeNodes(root->right);
    delete root;
}

TEST(t0, t1) {
    int n = 3;
#define null optional<int>()
    vector<vector<optional<int>>> output = {{1, null, 2, null, 3},
                                            {1, null, 3, 2},
                                            {2, 1, 3},
                                            {3, 1, null, null, 2},
                                            {3, 2, null, 1}};
    Solution sl;
    auto ret = sl.GenerateTrees(n);
    auto flatted = Flattern(ret);
    std::set<vector<optional<int>>> flatted_set(flatted.begin(), flatted.end());
    std::set<vector<optional<int>>> output_set(output.begin(), output.end());
    EXPECT_EQ(flatted_set, output_set);

    for (auto& ptr : ret) {
        FreeNodes(ptr);
    }
}

TEST(t0, t2) {
    int n = 1;
#define null optional<int>()
    vector<vector<optional<int>>> output = {{1}};
    Solution sl;
    auto ret = sl.GenerateTrees(n);
    auto flatted = Flattern(ret);
    std::set<vector<optional<int>>> flatted_set(flatted.begin(), flatted.end());
    std::set<vector<optional<int>>> output_set(output.begin(), output.end());
    EXPECT_EQ(flatted_set, output_set);
    for (auto& ptr : ret) {
        FreeNodes(ptr);
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
