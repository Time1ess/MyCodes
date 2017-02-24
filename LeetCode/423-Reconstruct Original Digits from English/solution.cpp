// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-24 09:33
// Last modified: 2017-02-24 09:33
// Filename: solution.cpp
// Description:
class Solution {
public:
    string originalDigits(string s) {
        int digit_cnts[26] = {0};
        // Distinguish digit by a special character in following order:
        // z : zero
        // w : two
        // x : six
        // s : seven
        // v : five
        // f : four
        // o : one
        // r : three
        // g : eight
        // e : nine
        string digits[10] = {"zero", "two", "six", "seven", "five", "four", "one", "three", "eight", "nine"};
        string uniques = "zwxsvforge";
        char unique_nums[10] = {'0', '2', '6', '7', '5', '4', '1', '3', '8', '9'};
        string ans;
        int cnt = 0;
        for(auto c: s)
            digit_cnts[c - 'a']++;
        for(int i = 0; i < 10; i++)
        {
            cnt = digit_cnts[uniques[i] - 'a'];
            if(cnt <= 0)
                continue;
            ans.append(string(cnt, unique_nums[i]));
            for(auto c: digits[i])
                digit_cnts[c-'a'] -= cnt;
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};
