class Solution {
public:
    /*
     * @param nums: a sorted integer array
     * @param lower: An integer
     * @param upper: An integer
     * @return: a list of its missing ranges
     */
    vector<string> findMissingRanges(vector<int> &nums, int lower, int upper) {
        // write your code here
        vector<string> ans;
        vector<long long> longNums(nums.begin(), nums.end());
        longNums.push_back(static_cast<long long>(upper) + 1);
        int n = longNums.size();
        long long expect = lower;
        for(int i = 0; i < n; i++) {
            while(i + 1 < n && longNums[i] == longNums[i+1]) {
                i++;
            }
            long long diff = longNums[i] - expect;
            if(diff == 0) {
                expect++;
                continue;
            } else if(diff == 1) {
                ans.push_back(to_string(expect));
            } else {
                ans.push_back(to_string(expect) + "->" + to_string(longNums[i]-1));
            }
            expect = longNums[i] + 1;

        }
        return ans;
    }
};
