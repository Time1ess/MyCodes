class Solution {
public:
    /**
     * @param words1: a list of string
     * @param words2: a list of string
     * @param pairs: a list of string pairs
     * @return: return a boolean, denote whether two sentences are similar or not
     */
    bool isSentenceSimilarity(vector<string> &words1, vector<string> &words2, vector<vector<string>> &pairs) {
        // write your code here
        int n1 = words1.size(), n2 = words2.size();
        if(n1 != n2)
            return false;
        unordered_map<string, unordered_set<string>> trans;
        for(auto p: pairs) {
            trans[p[0]].insert(p[1]);
            trans[p[1]].insert(p[0]);
        }
        for(int i = 0; i < n1; i++)
            if(words1[i] != words2[i]
               && trans[words1[i]].find(words2[i]) == trans[words1[i]].end())
                return false;
        return true;
    }
};
