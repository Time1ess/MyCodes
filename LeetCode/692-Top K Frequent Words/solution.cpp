struct compare{
    bool operator()(const pair<string, int> &p,const pair<string, int> &q)
    {
        if((p.second > q.second) || (p.second == q.second && p.first < q.first))
            return true;
        return false;
    }
};


class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> cnt;
        for(auto word: words)
            cnt[word]++;
        priority_queue<pair<string, int>, vector<pair<string, int>>, compare> pq;
        int cur = 0;
        for(auto x: cnt)
        {
            if(cur < k)
            {
                pq.push(make_pair(x.first, x.second));
                cur++;
            }
            else
            {
                pair<string, int> t = pq.top();
                if(t.second < x.second || (t.second == x.second && t.first > x.first))
                {
                    pq.pop();
                    pq.push(make_pair(x.first, x.second));
                }
            }
        }
        vector<string> ans;
        while(!pq.empty())
        {
            ans.push_back(pq.top().first);
            pq.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
