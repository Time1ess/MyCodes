// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-26 10:07
// Last modified: 2016-10-26 10:07
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        map<int,int> nm;
        vector<int> ans;
        for(int i=0; i < nums1.size(); i++)
            nm[nums1[i]]++;
        for(int i=0; i < nums2.size(); i++)
            if(nm[nums2[i]]-->0)
                ans.push_back(nums2[i]);
        return ans;
    }
};
