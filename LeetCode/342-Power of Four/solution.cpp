// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-31 14:58
// Last modified: 2017-03-31 14:58
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool isPowerOfFour(int num) {
        int p4s[] = {1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 4194304, 16777216, 67108864, 268435456, 1073741824};
        for(auto x: p4s)
            if(num == x)
                return true;
        return false;
    }
};
