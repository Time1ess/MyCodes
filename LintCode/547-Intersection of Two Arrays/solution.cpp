class Solution {
public:
    
    /*
     * @param nums1: an integer array
     * @param nums2: an integer array
     * @return: an integer array
     */
    vector<int> intersection(vector<int> nums1, vector<int> nums2) {
        // write your code here
        unordered_set<int> nums;
        for(auto num: nums1)
            nums.insert(num);
        vector<int> ans;
        for(auto num: nums2)
            if(nums.find(num) != nums.end())
            {
                ans.push_back(num);
                nums.erase(num);
            }
        return ans;
    }
};
