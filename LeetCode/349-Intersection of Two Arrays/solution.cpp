// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-09-07 11:18
// Last modified: 2016-09-07 11:48
// Filename: solution.cpp
// Description:
/**
 *  * Return an array of size *returnSize.
 *   * Note: The returned array must be malloced, assume caller calls free().
 *    */
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        map<int, int> m1, m2;
        for(int i=0; i < nums1.size(); i++)
            m1[nums1[i]]++;
        for(int i=0; i < nums2.size(); i++)
        {
            if(m1[nums2[i]]!=0&&m2[nums2[i]]==0)
                ans.push_back(nums2[i]);
            m2[nums2[i]]++;
        }
        return ans;
    }
};
