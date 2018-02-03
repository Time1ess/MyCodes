class Solution {
public:
    /*
     * @param nums: an array with positive and negative numbers
     * @param k: an integer
     * @return: the maximum average
     */
    double maxAverage(vector<int> &nums, int k) {
        int size = nums.size();
        vector<double> prefix_sum(size+1, 0);
        double l = INT_MAX, r = INT_MIN;
        for(auto x: nums)
        {    
            if(x < l)
                l = x;
            if(x > r)
                r = x;
        }
        while((r - l) > 1e-6)
        {
            double m = l + (r - l) / 2;
            double pre = 0;
            prefix_sum[0] = 0;
            bool found = false;
            for(int i = 1; i <= size; i++)
            {
                prefix_sum[i] = prefix_sum[i-1] + nums[i-1] - m;
                if(i >= k && prefix_sum[i] - pre >= 0)
                {
                    found = true;
                    break;
                }
                if(i >= k)
                    pre = min(pre, prefix_sum[i - k + 1]);
            }
            if(found)
                l = m;
            else
                r = m;
        }
        return l;
    }
};
