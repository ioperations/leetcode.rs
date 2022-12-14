/**
 * Definition for singly-linked list.
 */

#include <vector>

/**
 *  @brief 单链表节点
 */
struct ListNode {
    //! 值
    int val;
    //! 下一个节点
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode* MergeTwoListsV2(ListNode* list1, ListNode* list2) {
        ListNode* local_1 = list1;
        ListNode* local_2 = list2;
        ListNode dummy, *it = &dummy;

        while (local_1 != nullptr && local_2 != nullptr) {
            if (local_1->val < local_2->val) {
                it->next = local_1;
                local_1 = local_1->next;
            } else {
                it->next = local_2;
                local_2 = local_2->next;
            }
            it = it->next;
        }
        if (local_1 == nullptr) {
            it->next = local_2;
        } else if (local_2 == nullptr) {
            it->next = local_1;
        }
        return dummy.next;
    }

    ListNode* MergeTwoLists(ListNode* list1, ListNode* list2) {
        bool not_assign = true;

        ListNode* ret = nullptr;
        ListNode* head = nullptr;
        ListNode* pre = nullptr;

        for (;;) {
            if (list1 != nullptr && list2 != nullptr) {
                if (list1->val < list2->val) {
                    ret = list1;
                    list1 = list1->next;
                } else {
                    ret = list2;
                    list2 = list2->next;
                }
            } else if (list1 == nullptr && list2 != nullptr) {
                ret = list2;
                list2 = list2->next;
            } else if (list2 == nullptr && list1 != nullptr) {
                ret = list1;
                list1 = list1->next;
            } else {
                break;
            }
            if (not_assign) {
                head = ret;
                not_assign = false;
            } else {
                pre->next = ret;
            }
            pre = ret;

            ret = ret->next;
        }
        return head;
    }
};

#include <gtest/gtest.h>

#include <iostream>
void FreeList(ListNode* root) {
    if (root == nullptr) return;
    FreeList(root->next);
    delete root;
}

ListNode* ConstructList(const std::vector<int>& ele) {
    int size = ele.size();
    ListNode dummy, *it = &dummy;
    for (int i = 0; i < size; i++) {
        it->next = new ListNode(ele[i]);
        it = it->next;
    }

    return dummy.next;
}

TEST(t0, t1) {
    ListNode* s1 = ConstructList(std::vector<int>{1, 2, 4});

    ListNode* l1 = ConstructList(std::vector<int>{1, 3, 4});

    Solution sl;
    auto* it = sl.MergeTwoLists(s1, l1);

    std::vector<int> expected{1, 1, 2, 3, 4, 4};

    auto* it_2 = it;
    for (auto& ptr : expected) {
        EXPECT_EQ(ptr, it->val);
        it = it->next;
    }

    FreeList(it_2);
}
TEST(t1, t1) {
    ListNode* s1 = ConstructList(std::vector<int>{1, 2, 4});

    ListNode* l1 = ConstructList(std::vector<int>{1, 3, 4});

    Solution sl;
    auto* it = sl.MergeTwoListsV2(s1, l1);
    auto* it_2 = it;

    std::vector<int> expected{1, 1, 2, 3, 4, 4};

    for (auto& ptr : expected) {
        EXPECT_EQ(ptr, it->val);
        it = it->next;
    }

    FreeList(it_2);
}

TEST(t0, t3) {
    ListNode l1;
    l1.val = 0;

    Solution sl;
    auto* it = sl.MergeTwoLists(nullptr, &l1);

    EXPECT_EQ(it->val, 0);
    EXPECT_EQ(it->next, nullptr);
}

TEST(t0, t2) {
    Solution sl;
    auto* it = sl.MergeTwoLists(nullptr, nullptr);

    if (it != nullptr) {
        assert(false);
    }
}

#include <benchmark/benchmark.h>

#include <algorithm>
#include <vector>

static void Benchmakrv1(benchmark::State& state) {
    std::vector<int> t{1,  2,  3,  4,  5,  6,  7,  8, 9,
                       10, 11, 12, 13, 14, 15, 16, 17};

    std::vector<int> expected;
    int size = t.size();
    expected.reserve(size * 2);
    for (int i = 0; i < size; i++) {
        expected.push_back(t[i]);
        expected.push_back(t[i]);
    }

    for (auto _ : state) {
        ListNode* s1 = ConstructList(t);

        ListNode* l1 = ConstructList(t);

        Solution sl;
        auto* it = sl.MergeTwoLists(s1, l1);
        auto* it2 = it;

        for (auto& ptr : expected) {
            EXPECT_EQ(ptr, it->val);
            it = it->next;
        }

        FreeList(it2);
    }
}
BENCHMARK(Benchmakrv1);

static void Benchmakrv2(benchmark::State& state) {
    std::vector<int> t{1,  2,  3,  4,  5,  6,  7,  8, 9,
                       10, 11, 12, 13, 14, 15, 16, 17};

    std::vector<int> expected;
    int size = t.size();
    expected.reserve(size * 2);
    for (int i = 0; i < size; i++) {
        expected.push_back(t[i]);
        expected.push_back(t[i]);
    }
    sort(expected.begin(), expected.end());

    for (auto _ : state) {
        ListNode* s1 = ConstructList(t);

        ListNode* l1 = ConstructList(t);

        Solution sl;
        auto* it = sl.MergeTwoListsV2(s1, l1);

        auto* it2 = it;

        for (auto& ptr : expected) {
            EXPECT_EQ(ptr, it->val);
            it = it->next;
        }

        FreeList(it2);
    }
}
BENCHMARK(Benchmakrv2);

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();
    return ret;
}
