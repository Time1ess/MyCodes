// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-15 14:15
// Last modified: 2017-10-15 14:15
// Filename: solution.cpp
// Description:
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int total = 0, start = 0, tank = 0;
        for(int i = 0; i < gas.size(); i++)
        {
            tank += gas[i] - cost[i];
            if(tank < 0)
            {
                start = i + 1;
                total += tank;
                tank = 0;
            }
        }
        return total + tank >= 0 ? start : -1;
    }
};
