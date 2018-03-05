class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        stack<pair<int, int>> s;
        stack<int> total;
        vector<int> ans(n, 0);
        int m = logs.size();
        total.push(0);
        for(int i = 0; i < m; i++)
        {
            int fsemi = logs[i].find(':');
            int ssemi = logs[i].rfind(':');
            int fid = stoi(logs[i].substr(0, fsemi));
            bool is_start = logs[i].substr(fsemi + 1, ssemi - fsemi - 1) == "start";
            int ts = stoi(logs[i].substr(ssemi + 1));
            if(s.empty() || is_start)
            {
                s.push({fid, ts});
                total.push(0);
            }
            else
            {
                pair<int, int> top = s.top();
                s.pop();
                ans[top.first] += ts - top.second + 1 - total.top();
                total.pop();
                total.top() += ts - top.second + 1;
            }
        }
        return ans;
    }
};
