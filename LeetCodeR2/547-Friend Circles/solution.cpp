
class Solution {
public:
    int find(vector<int> &parents, int x)
    {
        if(parents[x] != x)
            parents[x] = find(parents, parents[x]);
        return parents[x];
    }
    void union_merge(vector<int> &parents, int x1, int px1, int x2, int px2)
    {
        parents[px1] = px2;
    }
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        if(n == 0)
            return 0;
        vector<int> parents(n, 0);
        for(int i = 0; i < n; i++)
            parents[i] = i;
        int ans = 0;
        for(int x1 = 0; x1 < n; x1++)
            for(int x2 = x1 + 1; x2 < n; x2++)
            {
                if(M[x1][x2] != 1)
                    continue;
                int px1 = find(parents, x1);
                int px2 = find(parents, x2);
                if(px1 == px2)
                    continue;
                union_merge(parents, x1, px1, x2, px2);
            }
        unordered_set<int> unique_parents;
        for(int x = 0; x < n; x++)
        {
            int px = find(parents, x);
            if(unique_parents.find(px) != unique_parents.end())
                continue;
            ans++;
            unique_parents.insert(px);
        }
        return ans;
    }
};
