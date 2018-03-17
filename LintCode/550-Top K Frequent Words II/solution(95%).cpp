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

class TopK {
private:
    vector<string> ans;
    unordered_map<string, int> cnts;
    unordered_set<string> pq_cands;
    priority_queue<PSI, vector<PSI>, Compare> pq;
    int k;
public:
    /*
    * @param k: An integer
    */TopK(int k) {
        this->k = k;
        // do intialization if necessary
    }

    /*
     * @param word: A string
     * @return: nothing
     */
    void add(string &word) {
        if(k <= 0)
            return;
        // write your code here
        cnts[word]++;
        PSI x{word, cnts[word]};
        if(pq_cands.find(word) == pq_cands.end())
        {
            // Word not in pq
            // update both pq and pq_cands
            if(pq.size() < k)
            {
                pq.push(x);
                pq_cands.insert(word);
                ans.clear();
            }
            else if(pq.size() == k && cmp(x, pq.top()))
            {
                pq_cands.erase(pq.top().first);
                pq_cands.insert(word);
                pq.pop();
                pq.push(x);
                ans.clear();
            }
        }
        else
        {
            // Update freq in pq
            // No pq_cands modifications
            vector<PSI> tmp;
            while(pq.top().first != word)
            {
                tmp.push_back(pq.top());
                pq.pop();
            }
            pq.pop();
            pq.push(x);
            for(int i = 0; i < tmp.size(); i++)
                pq.push(tmp[i]);
            ans.clear();
        }
    }

    /*
     * @return: the current top k frequent words.
     */
    vector<string> topk() {
        if(k <= 0)
            return {};
        // write your code here
        if(!ans.empty())
            return ans;
        priority_queue<PSI, vector<PSI>, Compare> tmp(pq);
        while(!tmp.empty())
        {
            ans.push_back(tmp.top().first);
            tmp.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
