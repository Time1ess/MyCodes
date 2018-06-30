class Solution {
public:
    /**
     * @param nums:  a sorted integer array without duplicates
     * @return: the summary of its ranges
     */
    vector<string> summaryRanges(vector<int> &nums) {
        // Write your code here
        int n = nums.size();
        if(n == 0)
            return {};
        else if(n == 1)
            return {to_string(nums[0])};
        int s = nums[0];
        int e = s;
        vector<string> ans;
        for(int i = 1; i < n; i++) {
            if(nums[i] != e + 1) {
                if(s == e)
                    ans.push_back(to_string(s));
                else
                    ans.push_back(to_string(s) + "->" + to_string(e));
                s = e = nums[i];
                continue;
            }
            e++;
        }
        if(s == e)
            ans.push_back(to_string(s));
        else
            ans.push_back(to_string(s) + "->" + to_string(e));
        return ans;
    }
};
