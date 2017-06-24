// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-24 16:37
// Last modified: 2017-06-24 16:37
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
        priority_queue<int> ables;
        multiset<pair<int, int>> unables;
        
        for(int i = 0; i < Profits.size(); i++)
            if(Capital[i] <= W)
                ables.push(Profits[i]);
            else
                unables.emplace(Capital[i], Profits[i]);
                
        while(!ables.empty() && k)
        {
            W += ables.top(), ables.pop();
            k--;
            for(auto x = unables.begin(); !unables.empty() && x->first <= W; x = unables.erase(x))
                ables.push(x->second);
        }
        return W;
    }
};
