// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-19 09:43
// Last modified: 2017-07-19 09:43
// Filename: solution.cpp
// Description:
bool cmp(const int &a, const int &b)
{
    return a > b;
}
class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end(), cmp);
        int h = 0;
        int size = citations.size();
        for(int i = 0; i < size; i++)
            h = max(h, min(i+1, citations[i]));
        return h;
    }
};
