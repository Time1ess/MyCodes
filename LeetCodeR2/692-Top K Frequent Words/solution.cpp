bool cmp(const pair<string, int> &a, const pair<string, int> &b)
{
    if(a.second > b.second)
        return true;
    else if(a.second == b.second)
        return a.first < b.first;
    else
        return false;
}

struct Compare
{
    bool operator()(const pair<string, int> &a, const pair<string, int> &b)
    {
        return cmp(a, b);
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        map<string, int> word_cnts;
        for(auto word: words)
            word_cnts[word]++;
        priority_queue<pair<string, int>, vector<pair<string, int>>, Compare> pq;
        for(auto p: word_cnts)
        {
            if(pq.size() < k)
                pq.push(p);
            else
            {
                pair<string, int> top = pq.top();
                if(cmp(p, top))
                {
                    pq.pop();
                    pq.push(p);
                }
            }
        }
        vector<string> ans;
        while(!pq.empty())
        {
            string s = pq.top().first;
            pq.pop();
            ans.push_back(s);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
