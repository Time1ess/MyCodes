// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-29 09:50
// Last modified: 2017-06-29 09:50
// Filename: solution.cpp
// Description:
class Solution {
public:
    string getHint(string secret, string guess) {
        unordered_map<char, int> cnts;
        set<pair<char, int>> poss;
        for(int i = 0; i < secret.length(); i++)
        {
            cnts[secret[i]]++;
            poss.insert(make_pair(secret[i], i));
        }
        int A = 0, B = 0;
        for(int i = 0; i < guess.length(); i++)
            if(poss.find(make_pair(guess[i], i)) != poss.end())
                A++, cnts[guess[i]]--;
        for(int i = 0; i < guess.length(); i++)
            if(poss.find(make_pair(guess[i], i)) == poss.end() && cnts[guess[i]] > 0)
                B++, cnts[guess[i]]--;
        return to_string(A)+"A"+to_string(B)+"B";
    }
};
