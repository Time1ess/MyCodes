// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-11 14:07
// Last modified: 2017-02-11 14:07
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        int rows[3] = {0, 0, 0};
        vector<string> ans;
        vector<string> chars = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};
        for(int i=0; i < chars.size(); i++)
        {
            for(auto c:chars[i])
                rows[i] |= 1<<(c-'a');
        }
        int iword;
        for(auto word:words)
        {
            iword = 0;
            for(auto c:word)
                iword |= 1<<(c-'a');
            for(int i=0; i < 3; i++)
            {
                if((iword|rows[i])==rows[i])
                {
                    ans.push_back(word);
                    break;
                }
            }
        }
        return ans;
    }
};
