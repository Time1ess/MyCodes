typedef pair<string, int> PSI;

bool cmp(const PSI &a, const PSI &b)
{
    return a.second > b.second || (a.second == b.second && a.first < b.first);
}

struct Compare
{
    bool operator()(const PSI &a, const PSI &b)
    {
        return cmp(a, b);
    }
};

class Solution {
public:
    /**
     * @param words: an array of string
     * @param k: An integer
     * @return: an array of string
     */
    vector<string> topKFrequentWords(vector<string> &words, int k) {
        if(k <= 0)
            return {};
        // write your code here
        unordered_map<string, int> cnts;
        for(auto word: words)
            cnts[word]++;
        priority_queue<PSI, vector<PSI>, Compare> pq;
        for(auto p: cnts)
        {
            if(pq.size() < k)
                pq.push(p);
            else if(pq.size() == k && cmp(p, pq.top()))
            {
                pq.pop();
                pq.push(p);
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
