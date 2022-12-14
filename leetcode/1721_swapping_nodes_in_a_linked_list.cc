/*
You are given the head of a linked list, and an integer k.

Return the head of the linked list after swapping the values of the kth node
from the beginning and the kth node from the end (the list is 1-indexed).
*/

#include <iostream>
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
    ListNode* SwapNodes(ListNode* head, int k) {
        // pass
        if (head == nullptr) {
            return nullptr;
        }

        ListNode* node1;
        ListNode* my_head = head;
        for (int i = 1; i < k && my_head != nullptr; i++) {
            my_head = my_head->next;
        }
        node1 = my_head;

        ListNode* node2 = head;

        my_head = my_head->next;
        while (my_head != nullptr) {
            my_head = my_head->next;
            node2 = node2->next;
        }
        std::swap(node1->val, node2->val);
        return head;
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
TEST(memleak, t1) {
    ListNode* head = ConstuctList(std::vector<int>{3, 2, 0, -4});

    FreeList(head);
}

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> v{1, 2, 3, 4, 5};
    int k = 2;

    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.SwapNodes(head, k);

    ExpectEqList(head, std::vector<int>{1, 4, 3, 2, 5});
    FreeList(head);
}

TEST(t0, t2) {
    std::vector<int> v{7, 9, 6, 6, 7, 8, 3, 0, 9, 5};
    int k = 5;

    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.SwapNodes(head, k);

    ExpectEqList(head, std::vector<int>{7, 9, 6, 6, 8, 7, 3, 0, 9, 5});
    FreeList(head);
}

TEST(t0, t3) {
    std::vector<int> v{1, 2};
    int k = 1;

    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.SwapNodes(head, k);

    ExpectEqList(head, std::vector<int>{2, 1});
    FreeList(head);
}

TEST(t0, t4) {
    std::vector<int> v{1, 2};
    int k = 2;

    ListNode* head = ConstuctList(v);
    Solution sl;
    head = sl.SwapNodes(head, k);

    ExpectEqList(head, std::vector<int>{2, 1});
    FreeList(head);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
