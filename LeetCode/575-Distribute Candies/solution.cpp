// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-09 14:09
// Last modified: 2017-05-09 14:09
// Filename: solution.cpp
// Description:
class Solution {
public:
    int distributeCandies(vector<int>& candies) {
        int size = candies.size();
        if(size == 0)
            return 0;
        unordered_set<int> s;
        for(auto x: candies)
            s.insert(x);
        return min(int(s.size()), size/2);
    }
};
