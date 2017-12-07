class Solution {
public:
    bool areSentencesSimilar(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        int size1 = words1.size(), size2 = words2.size();
        if(size1 != size2)
            return false;
        unordered_map<string, unordered_set<string>> sims;
        for(auto x: pairs)
        {
            sims[x.first].insert(x.second);
            sims[x.second].insert(x.first);
        }
        for(int i = 0; i < size1; i++)
        {
            if(words1[i] == words2[i])
                continue;
            if(sims.find(words1[i]) == sims.end() || sims[words1[i]].find(words2[i]) == sims[words1[i]].end())
                return false;
        }
        return true;
    }
};
