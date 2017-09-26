// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-26 10:44
// Last modified: 2017-09-26 10:44
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int kEmptySlots(vector<int>& flowers, int k) {
        int size = flowers.size();
        if(k >= size)
            return -1;
        vector<int> blooming(size + 1, 0);
        for(int i = 0; i < size; i++)
            blooming[flowers[i]] = i + 1;
        int left = 1, right = k + 2, maxday = max(blooming[left], blooming[right]);
        int ans = 1e6;
        while(right <= size)
        {
            int cnt = 0;
            for(int i = left + 1; i < right; i++)
            {
                if(blooming[i] > maxday)
                    cnt++;
                else if(blooming[i] < blooming[left] || blooming[i] < blooming[right])
                {
                    left = i - 1;
                    right = i + k;
                    break;
                }
            }
            if(cnt == k)
                ans = min(ans, maxday);
            maxday = max(blooming[++left], blooming[++right]);
        }
        if(ans != 1e6)
            return ans;
        return -1;
    }
};
