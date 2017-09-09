// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-09 10:50
// Last modified: 2017-09-09 10:50
// Filename: solution.cpp
// Description:
class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        int size = A.size();
        if(size <= 1)
            return 0;
        int sum = 0, ans = 0, asum = 0;
        for(int i = 0; i < size; i++)
        {
            sum += i * A[i];
            asum += A[i];
        }
        ans = sum;
        for(int i = size - 1; i >= 1; i--)
        {
            sum = sum + asum - size * A[i];
            ans = max(sum, ans);
        }
        return ans;
    }
};
