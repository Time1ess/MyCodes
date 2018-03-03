class Solution {
public:
    bool canFinish(int n, vector<pair<int, int>>& prerequisites) {
        unordered_map<int, unordered_set<int>> pres;
        vector<int> in_degrees(n, 0);
        for(auto x: prerequisites)
        {
            pres[x.second].insert(x.first);
            in_degrees[x.first]++;
        }
        while(true)
        {
            int idx = 0;
            for(; idx < n; idx++)
                if(in_degrees[idx] == 0)
                    break;
            if(idx == n)
                break;
            for(auto x: pres[idx])
                in_degrees[x]--;
            in_degrees[idx] = -1;
            pres.erase(idx);
        }
        for(auto x: in_degrees)
            if(x != -1)
                return false;
        return true;
    }
};
