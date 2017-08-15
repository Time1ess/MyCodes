// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-15 20:15
// Last modified: 2017-08-15 20:15
// Filename: solution2.cpp
// Description:
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0, right = arr.size(), size = arr.size();
        while(left < right)
        {
            int mid = left + ((right - left) >> 1);
            if(arr[mid] == x)
                right = mid;
            else if(arr[mid] > x)
                right = mid;
            else
                left = mid+1;
        }
        if(left > 0)
            left = abs(arr[left-1]) < abs(arr[left]) ? left - 1: left;
        right = left + 1;
        vector<int> ans;
        while(ans.size() < k)
            if(right < size && left >= 0)
                ans.push_back(abs(arr[left] - x) > abs(arr[right] - x) ? arr[right++] : arr[left--]);
            else if(right < size)
                ans.push_back(arr[right++]);
            else
                ans.push_back(arr[left--]);
        sort(ans.begin(), ans.end());
        return ans;
    }
};
