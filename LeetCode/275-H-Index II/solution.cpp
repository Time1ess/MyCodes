// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-19 09:47
// Last modified: 2017-07-19 09:47
// Filename: solution.cpp
// Description:
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int size = citations.size();
        int h = 0, th;
        for(int i = size - 1; i >= 0; i--)
        {
            th = min(size - i, citations[i]);
            if(th < h)
                break;
            h = th;
        }
        return h;
    }
};
