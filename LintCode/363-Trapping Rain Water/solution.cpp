class Solution {
public:
    /**
     * @param heights: a list of integers
     * @return: a integer
     */
    int trapRainWater(vector<int> &heights) {
        // write your code here
        int n = heights.size();
        if(n <= 2)
            return 0;
        int max_l = 0, max_r = 0, l = 0, r = n - 1;
        int ans = 0;
        while(l <= r)
        {
            if(heights[l] < heights[r])
            {
                if(heights[l] > max_l)
                    max_l = heights[l];
                else
                    ans += max_l - heights[l];
                l++;
            }
            else
            {
                if(heights[r] > max_r)
                    max_r = heights[r];
                else
                    ans += max_r - heights[r];
                r--;
            }
        }
        return ans;
    }
};
