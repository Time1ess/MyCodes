class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        map<int, int> begin, end, cnt;
        int x;
        int max_cnt = 0;
        for(int i = 0; i < nums.size(); i++)
        {
            x = nums[i];
            if(begin.find(x) == begin.end())
                begin[x] = i;
            end[x] = i;
            cnt[x] ++;
            if(cnt[x] > max_cnt)
                max_cnt = cnt[x];
        }
        int min_len = INT_MAX;
        for(auto x: cnt)
            if(x.second == max_cnt)
                min_len = min(min_len, end[x.first] - begin[x.first] + 1);
        return min_len;
    }
};
