// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-24 16:28
// Last modified: 2017-06-24 16:28
// Filename: solution.cpp
// Description:
class Solution {
public:
    int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
        vector<pair<int, int>> pcs;
        for(int i = 0; i < Profits.size(); i++)
            pcs.push_back(make_pair(Capital[i], Profits[i]));
        sort(pcs.begin(), pcs.end());
        int idx = 0;
        priority_queue<int> pq;
        for(; idx < pcs.size() && pcs[idx].first <= W; idx++)
            pq.push(pcs[idx].second);
        while(!pq.empty() && k)
        {
            int top = pq.top();
            pq.pop();
            W += top;
            k--;
            for(;idx < pcs.size() && pcs[idx].first <= W; idx++)
                pq.push(pcs[idx].second);
        }
        return W;
    }
};
