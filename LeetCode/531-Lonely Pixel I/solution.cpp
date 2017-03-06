// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-06 20:45
// Last modified: 2017-03-06 20:45
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& picture) {
        int r = picture.size(), c = picture[0].size();
        map<int, int> rcnt, ccnt;
        vector<pair<int, int>> bs;
        int cnt = 0;
        for(int i = 0; i < r; i ++)
            for(int j = 0; j < c; j++)
            {
                if(picture[i][j] == 'B')
                {
                    bs.push_back(make_pair(i, j));
                    rcnt[i]++;
                    ccnt[j]++;
                }
            }
        for(auto p: bs)
            if(rcnt[p.first] == 1 && ccnt[p.second] == 1)
                cnt++;
        return cnt;
    }
};
