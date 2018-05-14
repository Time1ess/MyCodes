bool cmp(const int &a, const int &b)
{
    string sa = to_string(a), sb = to_string(b);
    return sa + sb > sb + sa;
}

class Solution {
public:
    /**
     * @param nums: A list of non negative integers
     * @return: A string
     */
    string largestNumber(vector<int> &nums) {
        // write your code here
        sort(nums.begin(), nums.end(), cmp);
        string ans = "";
        for(auto x: nums)
            ans += to_string(x);
        int leading_zeros = 0;
        int n = ans.length();
        for(leading_zeros = 0; leading_zeros < n - 1; leading_zeros++)
            if(ans[leading_zeros] != '0')
                break;
        return ans.substr(leading_zeros);
    }
};
