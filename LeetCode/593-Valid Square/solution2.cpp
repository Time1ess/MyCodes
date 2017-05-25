// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-25 09:28
// Last modified: 2017-05-25 09:28
// Filename: solution2.cpp
// Description:
class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<vector<int>> ps{p1, p2, p3, p4};
        set<int> s;
        for(int i = 0; i < 4; i ++)
            for(int j = i + 1; j < 4; j++)
            {
                s.insert((ps[i][0]-ps[j][0]) * (ps[i][0]-ps[j][0]) + (ps[i][1]-ps[j][1]) * (ps[i][1]-ps[j][1]));
                if(s.size() > 2)
                    return false;
            }
        return s.count(0) == 0;
    }
};
