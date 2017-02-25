// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-25 15:33
// Last modified: 2017-02-25 15:33
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int maxProduct(vector<string>& words) {
        int ans=0;
        int size = words.size();
        if(!size)
            return 0;
        int w[size]={0}, c[size]={0};
        for(int i=0; i < size; i++)
        {
            for(char ch: words[i])
            {
                w[i] |= 1 << (ch - 'a');
                c[i] ++;
            }
        }
        for(int i=0; i < size; i++)
            for(int j=i; j < size; j++)
                if(!(w[i] & w[j]))
                    ans = max(ans, c[i] * c[j]);
        return ans;
    }
};
