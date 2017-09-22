// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-22 08:45
// Last modified: 2017-09-22 08:45
// Filename: solution.cpp
// Description:
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int cnt = m + n;
        while(cnt)
        {
            if(m && n)
                nums1[--cnt] = nums1[m-1] > nums2[n-1] ? nums1[--m]: nums2[--n];
            else if(m)
                nums1[--cnt] = nums1[--m];
            else
                nums1[--cnt] = nums2[--n];
        }
    }
};
