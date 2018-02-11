class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        vector<int> cands;
        unordered_map<int, int> cnts, first, last;
        for(int i = 0; i < nums.size(); i++)
        {
            cnts[nums[i]]++;
            if(first.find(nums[i]) == first.end())
                first[nums[i]] = i;
            last[nums[i]] = i;
        }
        int max_cnt = 0;
        for(auto it: cnts)
            max_cnt = max(max_cnt, it.second);
        int length = INT_MAX;
        for(auto it: cnts)
        {
            int key = it.first;
            int cnt = it.second;
            if(cnt < max_cnt)
                continue;
            length = min(length, last[key] - first[key] + 1);
        }
        return length;
    }
};
