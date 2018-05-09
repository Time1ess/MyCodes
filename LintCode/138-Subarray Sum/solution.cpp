class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A list of integers includes the index of the first number and the index of the last number
     */
    vector<int> subarraySum(vector<int> &nums) {
        // write your code here
        unordered_map<int, int> sum_pos;
        int sum = 0;
        sum_pos[0] = -1;
        int n = nums.size();
        for(int i = 0; i < n; i++)
        {
            sum += nums[i];
            if(sum_pos.find(sum) != sum_pos.end())
                return {sum_pos[sum]+1, i};
            sum_pos[sum] = i;
        }
        return {-1, -1};
    }
};
