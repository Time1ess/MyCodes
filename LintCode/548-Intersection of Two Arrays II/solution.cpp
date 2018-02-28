class Solution {
public:
    
    /*
     * @param nums1: an integer array
     * @param nums2: an integer array
     * @return: an integer array
     */
    vector<int> intersection(vector<int> nums1, vector<int> nums2) {
        // write your code here
        unordered_map<int, int> nums;
        for(auto num: nums1)
            nums[num]++;
        vector<int> ans;
        for(auto num: nums2)
            if(nums[num] > 0)
            {
                ans.push_back(num);
                nums[num]--;
            }
        return ans;
    }
};
