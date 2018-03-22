class Solution {
public:
    /**
     * @param nums:  an array of n integers
     * @param target: a target
     * @return: the number of index triplets satisfy the condition nums[i] + nums[j] + nums[k] < target
     */
    int threeSumSmaller(vector<int> &nums, int target) {
        // Write your code here
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int ans = 0;
        for(int i = 1; i < n - 1; i++)
        {
            int l = 0, r = n - 1;
            while(l < i && i < r)
            {
                int s = nums[l] + nums[i] + nums[r];
                if(s < target)
                {
                    ans += r - i;
                    l++;
                }
                else
                    r--;
            }
        }
        return ans;
    }
};
