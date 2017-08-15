// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-15 20:48
// Last modified: 2017-08-15 20:48
// Filename: solution3.cpp
// Description:
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int index = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int i = index - 1, j = index;
        while(k--)
            if(i < 0 ||(j < arr.size() && abs(arr[i] - x) > abs(arr[j] - x)))
                j++;
            else
                i--;
        return vector<int>(arr.begin() + i + 1, arr.begin() + j);
    }
};
