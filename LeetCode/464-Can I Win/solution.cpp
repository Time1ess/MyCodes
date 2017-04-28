// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-28 13:40
// Last modified: 2017-04-28 13:40
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool DFS_win(unordered_map<int, bool> &status, int current, int &max_choose, int total)
    {
        if(total <= 0)
            return false;
        if(status.find(current) != status.end())
            return status[current];
        for(int i = 1; i <= max_choose; i++)
        {
            if(current == (current | 1<<(i-1)))
                continue;
            if(!DFS_win(status, current | 1<<(i-1), max_choose, total-i))
            {
                status[current] = true;
                return true;
            }
        }
        status[current] = false;
        return status[current];
    }
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if((1+maxChoosableInteger) * maxChoosableInteger / 2 < desiredTotal)
            return false;
        if(desiredTotal <= 0)
            return true;
        unordered_map<int, bool> status;
        int current = 0;
        return DFS_win(status, current, maxChoosableInteger, desiredTotal);
    }
};
