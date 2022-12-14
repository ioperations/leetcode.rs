#include <vector>
class Solution {
   public:
    Solution(){};
    virtual ~Solution(){};

    double FindMedianSortedArrays(std::vector<int>& nums1,
                                  std::vector<int>& nums2) {
        std::vector<int> merged;
        const int size = nums1.size() + nums2.size();
        merged.reserve(size);

        std::size_t i = 0, j = 0;

        for (; i < nums1.size() || j < nums2.size();) {
            if (i < nums1.size() && j < nums2.size()) {
                if (nums1[i] < nums2[j]) {
                    merged.push_back(nums1[i]);
                    i++;
                } else {
                    merged.push_back(nums2[j]);
                    j++;
                }
            } else if (i == nums1.size()) {
                merged.push_back(nums2[j]);
                j++;
            } else if (j == nums2.size()) {
                merged.push_back(nums1[i]);
                i++;
            }
        }

        if (size % 2 == 1) {
            return merged[(size - 1) / 2];
        }

        return (double)(merged[(size - 1) / 2] + merged[(size) / 2]) / 2;
    }

   private:
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    Solution s;
    std::vector<int> nums1{1, 3};
    std::vector<int> nums2{2};
    double ret = s.FindMedianSortedArrays(nums1, nums2);
    EXPECT_EQ(ret, 2);
}

TEST(t0, t2) {
    Solution s;
    std::vector<int> nums1{1, 2};
    std::vector<int> nums2{3, 4};
    double ret = s.FindMedianSortedArrays(nums1, nums2);
    EXPECT_EQ(ret, 2.5);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
