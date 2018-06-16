class Solution {
public:
    /**
     * @param nums: a list of integer
     * @param k: an integer
     * @return: return an integer, denote the number of continuous subarrays whose sum equals to k
     */
    int subarraySumEqualsK(vector<int> &nums, int k) {
        // write your code here
        int n = nums.size();
        unordered_map<int, int> sumCnts;
        int sum = 0;
        int cnt = 0;
        sumCnts[0] = 1;
        for(int i = 0; i < n; i++)
        {
            sum += nums[i];
            cnt += sumCnts[sum-k];
            sumCnts[sum]++;
        }
        return cnt;
    }
};
