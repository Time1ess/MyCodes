// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-15 20:03
// Last modified: 2017-08-15 20:03
// Filename: solution.cpp
// Description:
class Compare
{
public:
    bool operator()(pair<int, int> &a, pair<int, int> &b)
    {
        return a.second > b.second || (a.second == b.second && a.first > b.first);
    }
};

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
        for(auto elem: arr)
            pq.push(make_pair(elem, abs(elem - x)));
        vector<int> ans;
        for(int i = 0; i < k; i++)
        {
            ans.push_back(pq.top().first);
            pq.pop();
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};
