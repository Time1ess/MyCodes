// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-24 17:21
// Last modified: 2017-06-24 17:21
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool validUtf8(vector<int>& data) {
        char high, low;
        bool continuation = false;
        int cnts = 0;
        for(int i = 0; i < data.size(); i++)
        {
            high = 0xF & (data[i]>>4);
            if(!continuation && (high & 0x8) == 0)
                continue;
            else if(!continuation && (high & 0xF) == 0xF)
            {
                low = 0xF & data[i];
                if((low & 0x8) != 0)
                    return false;
                continuation = true;
                cnts = 3;
            }
            else if(!continuation && (high & 0xE) == 0xE)
            {
                continuation = true;
                cnts = 2;
            }
            else if(!continuation && (high & 0xC) == 0xC)
            {
                continuation = true;
                cnts = 1;
            }
            else if(continuation && (high & 0x8) == 0x8)
            {
                cnts--;
                if(cnts < 0)
                    return false;
                else if(cnts == 0)
                    continuation = false;
            }
            else
                return false;
        }
        return true && !continuation;
    }
};
