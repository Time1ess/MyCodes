class Solution {
public:
    /*
     * @param nums: A list of integers
     * @return: nothing
     */
    void wiggleSort(vector<int> &nums) {
        // write your code here
        int n = nums.size();
        auto mid_it = nums.begin() + n / 2;
        nth_element(nums.begin(), mid_it, nums.end());
        int mid = *mid_it;
        int l = 0, r = n - 1, i = 0;
        
        #define reidx(x) nums[(1 + 2 * x) % (n | 1)]
        
        while(i <= r)
        {
            if(reidx(i) > mid)
                swap(reidx(i++), reidx(l++));
            else if(reidx(i) < mid)
                swap(reidx(i), reidx(r--));
            else
                i++;
        }
    }
};
