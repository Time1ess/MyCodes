class Solution {
public:
    /*
     * @param nums: a list of integers
     * @return: find a  majority number
     */
    int majorityNumber(vector<int> &nums) {
        // write your code here
        int n = nums.size(), cnt = 1, ans = nums[0];
        for(int i = 1; i < n; i++)
        {
            if(cnt == 0)
            {
                cnt = 1;
                ans = nums[i];
            }
            else if(nums[i] == ans)
                cnt++;
            else
                cnt--;
        }
        return ans;
    }
};
