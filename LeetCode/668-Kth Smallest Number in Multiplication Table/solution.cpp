// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-30 10:41
// Last modified: 2017-08-30 10:41
// Filename: solution.cpp
// Description:
class Solution {
public:
    int count(int mid, int m, int n) // In m x n table, how many elems are smaller than mid
    {
        int c = 0;
        for(int i = 1; i <= m; i++)
            c += min(mid / i, n);  // How many elems are smaller than mid at row i
        return c;
    }
    
    int findKthNumber(int m, int n, int k) {
        int low = 1, high = m * n + 1;
        while(low < high)
        {
            int mid = low + (high - low) / 2;
            if(count(mid, m, n) >= k)
                high = mid;
            else
                low = mid + 1;
        }
        return high;
    }
};
