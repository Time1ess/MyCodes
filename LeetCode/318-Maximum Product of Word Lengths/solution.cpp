// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-25 15:22
// Last modified: 2017-02-25 15:22
// Filename: solution.cpp
// Description:
class Solution {
public:
    int maxProduct(vector<string>& words) {
        int ans=0;
        for(auto word1: words)
            for(auto word2: words)
            {
                if(word1 == word2)
                    continue;
                int w1=0, w2=0, c1=0, c2=0;
                for(auto c: word1)
                {
                    w1 |= 1 << (c-'a');
                    c1 ++;
                }
                for(auto c: word2)
                {
                    w2 |= 1 << (c-'a');
                    c2 ++;
                }
                if(w1 & w2)
                    continue;
                ans = max(ans, c1 * c2);
            }
        return ans;
    }
};
