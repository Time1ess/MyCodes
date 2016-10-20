// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-20 18:52
// Last modified: 2016-10-20 18:52
// Filename: solution.cpp
// Description:
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        int cnt[11];
        cnt[1] = 10;
        if(n == 0)
            return 1;
        else if(n == 1)
            return cnt[1];
        else
        {
            for(int i=2; i <= n && i < 11; i++)
            {
                int c = 1;
                int k = i-1;
                int j = 9;
                c *= j;
                while(k--&&j)
                    c *= j--;
                cnt[i] = c;
            }
            int ans = 0;
            for(int i=1; i <= n && i < 11; i++)
                ans += cnt[i];
            return ans;
        }
    }
};
