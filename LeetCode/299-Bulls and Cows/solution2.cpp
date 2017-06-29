// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-29 09:56
// Last modified: 2017-06-29 09:56
// Filename: solution2.cpp
// Description:
class Solution {
public:
    string getHint(string secret, string guess) {
        vector<int> ss(10, 0), gs(10, 0);
        int A = 0, B = 0;
        for(int i = 0; i < secret.length(); i++)
            if(secret[i] == guess[i])
                A++;
            else
                ss[secret[i]-'0']++, gs[guess[i]-'0']++;
        for(int i = 0; i < ss.size(); i++)
            B += min(ss[i], gs[i]);
        return to_string(A)+"A"+to_string(B)+"B";
    }
};
