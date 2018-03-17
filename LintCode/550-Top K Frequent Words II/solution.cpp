map<string, int> cnts;

struct Compare
{
    bool operator()(const string &a, const string &b)
    {
        int cnt_a = cnts[a], cnt_b = cnts[b];
        if(cnt_a != cnt_b)
            return cnt_a > cnt_b;
        return a < b;
    }
};

class TopK {
private:
    set<string, Compare> words;
    int k;
public:
    /*
    * @param k: An integer
    */TopK(int k) {
        this->k = k;
        cnts.clear();
        // do intialization if necessary
    }

    /*
     * @param word: A string
     * @return: nothing
     */
    void add(string &word) {
        if(cnts.find(word) != cnts.end())
        {
            if(words.find(word) != words.end())
                words.erase(words.find(word));
            cnts[word] += 1;
        }
        else
            cnts[word] = 1;
        words.insert(word);
        if(words.size() > k)
            words.erase(--words.end());
    }

    /*
     * @return: the current top k frequent words.
     */
    vector<string> topk() {
        vector<string> ans;
        auto it = words.begin();
        for(int i = 0; i < k && it != words.end(); i++, it++)
            ans.push_back(*it);
        return ans;
    }
};
