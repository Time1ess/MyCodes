// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-19 09:49
// Last modified: 2017-07-19 09:49
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int size = citations.size();
        int left = 0, right = size - 1, mid;
        while(left <= right)
        {
            mid = left + (right - left) / 2;
            if(citations[mid] >= (size - mid))
                right = mid - 1;
            else
                left = mid + 1;
        }
        return size - left;
    }
};
