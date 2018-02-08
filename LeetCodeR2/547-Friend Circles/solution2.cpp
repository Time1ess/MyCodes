
class Solution {
public:
    int find(vector<int> &parents, int x)
    {
        if(parents[x] != x)
            parents[x] = find(parents, parents[x]);
        return parents[x];
    }
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        if(n == 0)
            return 0;
        vector<int> parents(n, 0);
        for(int i = 0; i < n; i++)
            parents[i] = i;
        int ans = n;
        for(int x1 = 0; x1 < n; x1++)
            for(int x2 = x1 + 1; x2 < n; x2++)
            {
                if(M[x1][x2] != 1)
                    continue;
                int px1 = find(parents, x1);
                int px2 = find(parents, x2);
                if(px1 == px2)
                    continue;
                parents[px1] = px2;
                ans--;
            }
        return ans;
    }
};
