// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-15 09:27
// Last modified: 2017-05-15 09:27
// Filename: solution.cpp
// Description:
class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.length(), len2 = word2.length();
        int lcs[len1+1][len2+1];
        memset(lcs, 0, sizeof(lcs));
        for(int i = 1; i <= len1; i++)
            for(int j = 1; j <= len2; j++)
                if(word1[i-1] == word2[j-1])
                    lcs[i][j] = lcs[i-1][j-1] + 1;
                else if(lcs[i-1][j] >= lcs[i][j-1])
                    lcs[i][j] = lcs[i-1][j];
                else
                    lcs[i][j] = lcs[i][j-1];
        return len1 + len2 - 2 * lcs[len1][len2];
    }
};
