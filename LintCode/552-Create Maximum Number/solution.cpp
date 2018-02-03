class Solution {
public:
    /*
     * @param nums1: an integer array of length m with digits 0-9
     * @param nums2: an integer array of length n with digits 0-9
     * @param k: an integer and k <= m + n
     * @return: an integer array
     */
    vector<int> max_array(const vector<int> &nums, int k)
    {
        vector<int> ans(k, 0);
        int size = nums.size();
        for(int i = 0, j = 0; i < size; i++)
        {
            while(size - i + j > k && j > 0 && ans[j-1] < nums[i])
                j--;
            if(j < k)
                ans[j++] = nums[i];
        }
        return ans;
    }
    vector<int> merge_array(const vector<int> &nums1, const vector<int> &nums2, int k)
    {
        vector<int> ans(k, 0);
        for(int i = 0, j = 0, r = 0; r < k ; r++)
            ans[r] = greater(nums1, i, nums2, j) ? nums1[i++] : nums2[j++];
        return ans;
    }
    
    bool greater(const vector<int> &nums1, int i, const vector<int> &nums2, int j)
    {
        while(i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j])
            i++, j++;
        return j == nums2.size() || (i < nums1.size() && nums1[i] > nums2[j]);
    }

    vector<int> maxNumber(vector<int> &nums1, vector<int> &nums2, int k) {
        vector<int> ans;
        int size_1 = nums1.size(), size_2 = nums2.size();
        // max(0, k - size_2) ensures nums2 always valid
        // i <= size_1 && i <= k ensures nums1 always valid
        for(int i = max(0, k - size_2); i <= size_1 && i <= k; i++)
        {
            vector<int> first = max_array(nums1, i);
            vector<int> second = max_array(nums2, k - i);
            vector<int> tmp = merge_array(first, second, k);
            if(greater(tmp, 0, ans, 0))
                ans = tmp;
        }
        return ans;
    }
};
