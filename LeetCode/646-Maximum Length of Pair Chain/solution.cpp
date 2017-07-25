// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-25 09:40
// Last modified: 2017-07-25 09:40
// Filename: solution.cpp
// Description:
bool cmp(const vector<int> &a, const vector<int> &b)
{
    return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]);
}
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), cmp);
        int size = pairs.size();
        int count = 0;
        int i = 0, j = 0;
        while(j < size)
        {
            if(j == 0 || pairs[i][1] < pairs[j][0])
            {
                count++;
                i = j;
            }
            j++;
        }
        return count;
    }
};
