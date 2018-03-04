class Solution {
public:
    int get_kth_small(vector<int> &nums1, vector<int> &nums2, int l1, int r1, int l2, int r2, int k)
    {
        if(l1 == r1)
            return nums2[l2 + k - 1];
        else if(l2 == r2)
            return nums1[l1 + k - 1];
        if(k == 1)
            return min(nums1[l1], nums2[l2]);
        int i = min(r1, l1 + k / 2);
        int j = min(r2, l2 + k / 2);
        if(nums1[i - 1] > nums2[j - 1])
            return get_kth_small(nums1, nums2, l1, r1, j, r2, k - j + l2);
        else
            return get_kth_small(nums1, nums2, i, r1, l2, r2, k - i + l1);
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        int l = (n + m + 1) >> 1;
        int r = (n + m + 2) >> 1;
        return (get_kth_small(nums1, nums2, 0, n, 0, m, l) + get_kth_small(nums1, nums2, 0, n, 0, m, r)) / 2.0;
    }
};
