// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-02 09:55
// Last modified: 2016-10-02 09:55
// Filename: solution.cpp
// Description:
bool cmp(const pair<int, int>& p, const pair<int, int>& q)
{
    return p.first > q.first || (p.first == q.first && p.second < q.second);
}
class Solution {
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        sort(people.begin(), people.end(), cmp);
        // people: height high...low   count: low...high
        vector<pair<int, int>> res;
        for(auto& x:people)
            res.insert(res.begin()+x.second, x);
        return res;
    }
};
