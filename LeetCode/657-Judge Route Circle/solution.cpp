// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-15 08:33
// Last modified: 2017-08-15 08:33
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool judgeCircle(string moves) {
        int offset[2] = {0};
        for(char move: moves)
            if(move == 'U' || move == 'D')
                offset[0] += move == 'U' ? 1 : -1;
            else
                offset[1] += move == 'L' ? 1 : -1;
        return offset[0] == 0 && offset[1] == 0;
    }
};
