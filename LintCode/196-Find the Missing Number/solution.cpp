class Solution {
public:
    /*
     * @param nums: An array of integers
     * @return: An integer
     */
    int findMissing(vector<int> nums) {
        // write your code here
        int n = nums.size();
        long long s = n;
        for(int i = 0; i < n; i++)
        {
            s += i;
            s -= nums[i];
        }
        return s;
    }
};
