// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-03 09:46
// Last modified: 2017-04-03 17:31
// Filename: solution.cpp
// Description:
class Solution {
public:
    int find(int x, int *p)
    {
        while(x != p[x])
        {
            p[x] = p[p[x]];
            x = p[x];
        }
        return p[x];
    }
    void merge_union(int x, int y, int *p, int *rank, int &cnt)
    {
        int px = find(x, p);
        int py = find(y, p);
        if(px == py)
            return;
        if(rank[px] > rank[py])
        {
            p[py] = px;
        }
        else
        {
            p[px] = py;
            if(rank[px] == rank[py])
                rank[py] += rank[px];
        }
        cnt--;
    }
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        if(n == 0)
            return 0;
        int p[n] = {0}, rank[n];
        for(int i = 0; i < n; i++)
        {
            p[i] = i;
            rank[i] = 1;
        }
        int cnt = n;
        for(int x = 0; x < n; x++)
            for(int y = x + 1; y < n; y++)
                if(M[x][y] == 1)
                    merge_union(x, y, p, rank, cnt);
        return cnt;
    }
};
