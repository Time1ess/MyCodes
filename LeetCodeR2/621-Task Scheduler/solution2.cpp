class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> cnts(26, 0);
        for(auto c: tasks)
            cnts[c-'A']++;
        priority_queue<int> pq;
        for(int i = 0; i < 26; i++)
            if(cnts[i] != 0)
                pq.push(cnts[i]);
        int ans = 0;
        vector<int> tmp;
        while(!pq.empty())
        {
            int k = n + 1;
            tmp.clear();
            while(k > 0 && !pq.empty())
            {
                int cnt = pq.top();
                pq.pop();
                k--;
                ans++;
                if(cnt > 1)
                    tmp.push_back(cnt - 1);
            }
            if(tmp.size() == 0)
                break;
            ans += k;
            for(auto x: tmp)
                pq.push(x);
        }
        return max(int(tasks.size()), ans);
    }
};
