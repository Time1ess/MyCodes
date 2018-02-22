struct Val
{
    int max_leading_sum, max_trailing_sum, max_sum, sum;
    Val(int ml, int mt, int ms, int s)
    {
        max_leading_sum = ml;
        max_trailing_sum = mt;
        max_sum = ms;
        sum = s;
    }
};
class Solution {
public:
    Val dac(vector<int> &nums, int start, int end)
    {
        if(start >= end)
            return Val(nums[start], nums[start], nums[start], nums[start]);
        int mid = start + (end - start) / 2;
        Val left = dac(nums, start, mid);
        Val right = dac(nums, mid + 1, end);
        int ml = max(left.max_leading_sum, left.sum + right.max_leading_sum);
        int mt = max(right.max_trailing_sum, right.sum + left.max_trailing_sum);
        int ms = max(left.max_trailing_sum + right.max_leading_sum, max(left.max_sum, right.max_sum));
        int s = left.sum + right.sum;
        return Val(ml, mt, ms, s);
    }
    int maxSubArray(vector<int>& nums) {
        Val ans = dac(nums, 0, nums.size() - 1);
        return ans.max_sum;
    }
};
