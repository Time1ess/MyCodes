// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-07 11:19
// Last modified: 2017-04-07 11:19
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int adding = 1, t;
        for(int i = digits.size()-1; i >= 0; i--)
        {
            t = digits[i] + adding;
            digits[i] = (t % 10);
            adding = t / 10;
        }
        if(adding == 1)
            digits.insert(digits.begin(), 1);
        return digits;
    }
};
