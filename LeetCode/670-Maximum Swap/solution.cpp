// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-05 14:22
// Last modified: 2017-09-05 14:22
// Filename: solution.cpp
// Description:
class Solution {
public:
    int maximumSwap(int num) {
        int digits[9] = {0};
        int k = 0, mod;
        while(num)
        {
            digits[k++] = num % 10;
            num /= 10;
        }
        int j = k - 1;
        while(j > 0 && digits[j] >= digits[j-1])  // Find end point for decreasing digits sequence
            j--;
        int max_idx = 0;
        for(int i = 1; i < j; i++)  // Find index for max digit in rest digits
            if(digits[i] > digits[max_idx])
                max_idx = i;
        for(int i = k - 1; i >= 0; i--)  // From highest digit to lowest, swap max digit and digit smaller than it
            if(digits[i] < digits[max_idx])
            {
                swap(digits[i], digits[max_idx]);
                break;
            }
        int ans = 0;
        for(int i = k - 1; i >= 0; i--)  // Reconstruct number
            ans = ans * 10 + digits[i];
        return ans;
    }
};
