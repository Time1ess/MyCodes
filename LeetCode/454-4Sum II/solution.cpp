// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-21 16:07
// Last modified: 2017-02-21 16:07
// Filename: solution.cpp
// Description:
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        map<int, int> mab, mcd;
        map<int, int>::iterator y;
        int cnt = 0;
        int size = A.size();
        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                mab[A[i]+B[j]]++, mcd[C[i]+D[j]]++;
        for(auto x: mab)
        {
            y = mcd.find(-(x.first));
            if(y!=mcd.end())
            {
                cnt += x.second * y->second;
            }
        }
        return cnt;
    }
};
