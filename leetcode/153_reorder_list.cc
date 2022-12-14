/*
You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln
Reorder the list to be on the following form:

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
You may not modify the values in the list's nodes. Only nodes themselves may be
changed.


*/

#include <queue>
#include <stack>
using namespace std;

//* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    void ReorderList(ListNode* head) { Solve(head); }

    void Solve(ListNode*& head) {
        std::stack<ListNode*> stack;
        std::queue<ListNode*> queue;

        ListNode* my_head = head;
        int size = 0;
        while (my_head != nullptr) {
            stack.push(my_head);
            queue.push(my_head);
            my_head = my_head->next;
            size++;
        }

        ListNode node;
        ListNode* it = &node;

        for (int i = 0; i < size;) {
            it->next = queue.front();
            it = it->next;
            queue.pop();
            it->next = stack.top();
            stack.pop();
            it = it->next;
            i += 2;
        }
        it->next = nullptr;
        head = node.next;
    }
};

#include <gtest/gtest.h>

#include <iostream>
ListNode* ConstuctList(const std::vector<int>& elemets) {
    ListNode head;
    ListNode* tail = &head;
    for (auto& pt : elemets) {
        tail->next = new ListNode(pt);
        tail = tail->next;
    }
    return head.next;
}

void FreeList(ListNode* head) {
    if (head == nullptr) {
        return;
    }
    FreeList(head->next);
    delete head;
}

void ExpectEqList(ListNode* const head, const std::vector<int>& elements) {
    int i = 0;
    ListNode* m_head = head;

    while (m_head != nullptr) {
        EXPECT_EQ(m_head->val, elements[i]);
        m_head = m_head->next;
        i++;
    }
    EXPECT_EQ(i, elements.size());
}
TEST(t0, t1) {
    std::vector<int> v = {1, 2, 3, 4};
    std::vector<int> output = {1, 4, 2, 3};

    /*
     ___      ___       ___       ___
    | 1 |    | 2 |     | 3 |     | 4 |
    |___|    |___|     |___|     |___|

     ___      ___       ___       ___
    | 1 |    | 4 |     | 2 |     | 3 |
    |___|    |___|     |___|     |___|

    */

    ListNode* head = ConstuctList(v);
    Solution sl;
    sl.ReorderList(head);

    ExpectEqList(head, output);
    FreeList(head);
}

TEST(t0, t2) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> output = {1, 5, 2, 4, 3};

    /*
     ___      ___       ___       ___       ___
    | 1 |    | 2 |     | 3 |     | 4 |     | 5 |
    |___|    |___|     |___|     |___|     |___|



     ___      ___       ___       ___       ___
    | 1 |    | 5 |     | 2 |     | 4 |     | 5 |
    |___|    |___|     |___|     |___|     |___|

    */
    ListNode* head = ConstuctList(v);
    Solution sl;
    sl.ReorderList(head);

    ExpectEqList(head, output);
    FreeList(head);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
