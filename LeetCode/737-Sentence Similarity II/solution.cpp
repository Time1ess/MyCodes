class Solution {
public:
    int uid = 0;
    map<string, int> word2int;
    int parents[1010] = {0};
    
    int find_parent(int x)
    {
        if(parents[x] != x)
            parents[x] = find_parent(parents[x]);
        return parents[x];
    }
    
    void union_merge(int x1, int x2, int p1, int p2)
    {
        parents[p2] = p1;
    }
    
    bool same_root(int x1, int x2)
    {
        return find_parent(x1) == find_parent(x2);
    }
    
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        int size1 = words1.size(), size2 = words2.size();
        int x1, x2, p1, p2;
        if(size1 != size2)
            return false;
        for(auto pair: pairs)
        {
            if(word2int.find(pair.first) == word2int.end())
                word2int[pair.first] = ++uid;
            if(word2int.find(pair.second) == word2int.end())
                word2int[pair.second] = ++uid;
            x1 = word2int[pair.first];
            x2 = word2int[pair.second];
            if(parents[x1] == 0)
                parents[x1] = x1;
            if(parents[x2] == 0)
                parents[x2] = x2;
            p1 = find_parent(x1);
            p2 = find_parent(x2);
            union_merge(x1, x2, p1, p2);
        }
        for(int i = 0; i < size1; i++)
            if(!same_root(word2int[words1[i]], word2int[words2[i]]))
                return false;
        return true;
    }
};
