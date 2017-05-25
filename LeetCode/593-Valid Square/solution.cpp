// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-25 09:25
// Last modified: 2017-05-25 09:25
// Filename: solution.cpp
// Description:
class Solution {
public:
    int dis(vector<int>& p1, vector<int> &p2)
    {
        return (p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]);
    }
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        unordered_set<int> s({dis(p1, p2), dis(p1, p3), dis(p1, p4), dis(p2, p3), dis(p2, p4), dis(p3, p4)});
        return s.count(0) == 0 && s.size() == 2;
    }
};
