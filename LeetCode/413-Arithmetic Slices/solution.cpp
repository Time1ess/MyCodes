// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-18 16:10
// Last modified: 2016-10-18 16:10
// Filename: solution.cpp
// Description:
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int size = A.size();
        if(size < 3)
            return 0;
        for(int i=0; i < size-1; i++)
            A[i] = A[i+1]-A[i];
        A.resize(size-1);
        size--;
        
        int res = 0;
        int len = 1;
        for(int i=1; i < size; i++)
        {
            if(A[i] == A[i-1])
                len++;
            else
            {
                res += len*(len-1)/2;
                len = 1;
            }
        }
        if(len > 1)
            res += len*(len-1)/2;
        return res;
    }
};
