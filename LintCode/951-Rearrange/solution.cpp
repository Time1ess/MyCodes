class Solution {
public:
    /**
     * @param nums: the num arrays 
     * @return: the num arrays after rearranging
     */
    vector<int> rearrange(vector<int> &nums) {
        // Write your code here 
        sort(nums.begin(), nums.end());
        vector<int> ans;
        int n = nums.size();
        for(int i = 0; i < n / 2; i++)
        {
            ans.push_back(nums[i]);
            ans.push_back(nums[i + (n+1) / 2]);
        }
        if(n & 0x1 == 1)
            ans.push_back(nums[n/2]);
        return ans;
    }
};
