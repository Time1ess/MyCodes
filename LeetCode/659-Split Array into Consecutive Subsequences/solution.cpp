// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-23 09:28
// Last modified: 2017-08-23 09:28
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool isPossible(vector<int>& nums) {
        map<int, int> cnts, wants;
        for(auto x: nums)
            cnts[x] ++;
        for(auto x: nums)
        {
            if(cnts[x] == 0)
                continue;
            else if(wants[x] > 0)
            {
                wants[x] --;
                wants[x+1] ++;
            }
            else if(cnts[x+1] > 0 && cnts[x+2] > 0)
            {
                cnts[x+1] --;
                cnts[x+2] --;
                wants[x+3] ++;
            }
            else
                return false;
            cnts[x] --;
        }
        return true;
    }
};
