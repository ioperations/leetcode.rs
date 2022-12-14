/*Given the root of a binary tree, return the sum of values of its deepest
 * leaves.*/

#include <algorithm>
#include <queue>

using namespace std;

//* Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    bool deleted = false;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};
class Solution {
   public:
    int Height(TreeNode* root) {
        if (!root) return 0;
        return std::max(Height(root->left), Height(root->right)) + 1;
    }
    int sum = 0;
    int SumAtK(TreeNode* root, int k) {
        if (!root) return sum;
        if (k == 0 && root->val != -1) sum = sum + root->val;
        SumAtK(root->left, k - 1);
        SumAtK(root->right, k - 1);
        return sum;
    }

    int DeepestLeavesSum(TreeNode* root) {
        int h = Height(root);
        int sum = SumAtK(root, h - 1);
        return sum;
    }
};

class SolutionV2 {
   public:
    int DeepestLeavesSum(TreeNode* root) {
        if (!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        q.push(nullptr);
        int sum = 0;
        while (q.size() > 1) {
            auto* curr = q.front();
            q.pop();
            if (!curr) {
                q.push(nullptr);
                sum = 0;
                continue;
            }
            sum += curr->val;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        return sum;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <vector>
using namespace std;

#define null -1

TreeNode* NewNode(int data) {
    TreeNode* node = new TreeNode;
    node->val = data;
    node->left = node->right = nullptr;
    return node;
}

// Function to insert nodes in level order
TreeNode* InsertLevelOrder(vector<int>& arr, TreeNode* root, int i) {
    // Base case for recursion
    int n = arr.size();
    if (i < n) {
        TreeNode* temp = NewNode(arr[i]);
        root = temp;

        // insert left child
        root->left = InsertLevelOrder(arr, root->left, 2 * i + 1);

        // insert right child
        root->right = InsertLevelOrder(arr, root->right, 2 * i + 2);

        if (arr[i] == -1) {
            root->deleted = true;
        }
    }
    return root;
}

// Function to print tree nodes in
// InOrder fashion
void InOrder(TreeNode* root, std::vector<string>& vec) {
    if (root != nullptr) {
        InOrder(root->left, vec);
        vec.push_back(std::to_string(root->val) +
                      (root->deleted ? "deleted" : "not deleted"));
        InOrder(root->right, vec);
    }
}

void BfsSearch(TreeNode* root, std::vector<std::string>& vec) {
    queue<TreeNode*> q;
    q.push(root);

    while (q.size()) {
        TreeNode* tmp = q.front();

        q.pop();

        if (tmp != nullptr) {
            q.push(tmp->left);
            q.push(tmp->right);
            vec.push_back(std::to_string(tmp->val) +
                          (tmp->deleted ? "deleted" : "not deleted"));
        }
    }
}

void FreeTreeNode(TreeNode* root) {
    if (root == nullptr) return;

    FreeTreeNode(root->left);
    FreeTreeNode(root->right);

    delete root;
}

TreeNode* ConstructTreeNode(std::vector<int>& arr) {
    TreeNode root;
    TreeNode* z = InsertLevelOrder(arr, &root, 0);

    return z;
}

TEST(t0, t1) {
    vector<int> vec = {1, 2, 3, 4, 5, null, 6, 7, null, null, null, null, 8};

    TreeNode* root = ConstructTreeNode(vec);
    int expected = 15;

    Solution sl;
    int ret = sl.DeepestLeavesSum(root);
    EXPECT_EQ(ret, expected);

    FreeTreeNode(root);
};

TEST(t0, t2) {
    vector<int> vec = {6, 7, 8, 2, 7, 1, 3, 9, null, 1, 4, null, null, null, 5};

    TreeNode* root = ConstructTreeNode(vec);
    int expected = 19;

    Solution sl;
    int ret = sl.DeepestLeavesSum(root);
    EXPECT_EQ(ret, expected);

    FreeTreeNode(root);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
