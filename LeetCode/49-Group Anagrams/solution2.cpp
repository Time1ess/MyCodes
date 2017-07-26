// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-26 10:40
// Last modified: 2017-07-26 10:40
// Filename: solution2.cpp
// Description:
class Solution {
private:
    int primes[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103};
public:
    int hash(string s)
    {
        int key = 1;
        for(auto c: s)
            key *= primes[c - 'a'];
        return key;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<int, vector<string>> m;
        for(auto str: strs)
        {
            m[hash(str)].push_back(str);
        }
        vector<vector<string>> ans;
        for(auto x: m)
            ans.push_back(x.second);
        return ans;
    }
};
