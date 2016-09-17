// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-09-17 14:26
// Last modified: 2016-09-17 14:26
// Filename: solution.cpp
// Description:
int b_search(vector<int>& numbers, int start, int end, int target)
    {
        if(end<=start)
            return end;
        int mid = (start+end)>>1;
        if(numbers[mid]>=target)
            return b_search(numbers, start, mid, target);
        else
            return b_search(numbers, mid+1, end, target);
    }

class Solution {
public:

    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> ans;
        int size = numbers.size();
        int idx;
        for(int i=0;i < size; i++)
        {
            idx = b_search(numbers, i+1, size-1, target-numbers[i]);
            if(numbers[idx]+numbers[i]==target)
            {
                ans.push_back(i+1);
                ans.push_back(idx+1);
                break;
            }
        }
        return ans;
    }

};
