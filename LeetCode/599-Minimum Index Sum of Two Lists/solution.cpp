// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-30 08:25
// Last modified: 2017-05-30 08:25
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> m;
        for(int i = 0; i < list1.size(); i++)
            m[list1[i]] = i;
        int cost = INT_MAX, tmp;
        vector<string> ans;
        for(int i = 0; i < list2.size(); i++)
        {
            if(m.find(list2[i]) != m.end())
            {
                tmp = i + m[list2[i]];
                if(tmp < cost)
                {
                    ans.clear();
                    ans.push_back(list2[i]);
                    cost = tmp;
                }
                else if(tmp == cost)
                    ans.push_back(list2[i]);
            }
        }
        return ans;
    }
};
