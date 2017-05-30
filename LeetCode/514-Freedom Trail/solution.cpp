// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-27 11:39
// Last modified: 2017-05-27 11:39
// Filename: solution.cpp
// Description:
class Solution {
public:
    int DFS(string &ring, string &key, int &rlen, int &klen, int mem[101][101], int ridx, int kidx)
    {
        if(kidx == klen)
            return 0;
        if(mem[ridx][kidx] != -1)
            return mem[ridx][kidx];
        int r = ridx, cnt = 0;
        int ans = INT_MAX;
        while(cnt++ < rlen)
        {
            if(ring[r] == key[kidx])
                ans = min(ans, min(abs(r-ridx), rlen - abs(r-ridx)) + DFS(ring, key, rlen, klen, mem, r, kidx+1));
            r = (r+1) % rlen;
        }
        mem[ridx][kidx] = ans;
        return ans;
    }
    int findRotateSteps(string ring, string key) {
        int rlen = ring.length(), klen = key.length();
        int mem[101][101];
        memset(mem, -1, sizeof(mem));
        int ans = DFS(ring, key, rlen, klen, mem, 0, 0);
        return ans + klen;
    }
};
