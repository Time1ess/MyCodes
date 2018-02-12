class Solution {
public:
    int numRabbits(vector<int>& answers) {
        unordered_map<int, int> cnts;
        int ans = 0;
        for(auto x: answers)
        {
            if(x == 0)
            {
                ans++;
                continue;
            }
            cnts[x]++;
        }
        for(auto x: cnts)
        {
            int key = x.first;
            int cnt = x.second;
            int pair = cnt / (key + 1);
            if(cnt % (key + 1) != 0)
                pair++;
            ans += (key + 1) * pair;
        }
        return ans;
    }
};
