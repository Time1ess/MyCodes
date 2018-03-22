class Solution {
public:
    /**
     * @param nums: a list of integer
     * @return: return a integer, denote  the maximum number of consecutive 1s
     */
    int findMaxConsecutiveOnes(vector<int> &nums) {
        // write your code here
        int l = 0, r = 0;
        bool can_flip = true;
        int n = nums.size();
        int ans = 0;
        while(r < n)
        {
            if(nums[r] == 1)
                r++;
            else if(can_flip)
            {
                can_flip = false;
                r++;
            }
            else
            {
                while(nums[l] != 0)
                    l++;
                l++;
                can_flip = true;
            }
            ans = max(ans, r - l);
        }
        return ans;
    }
};
