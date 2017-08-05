// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-05 09:20
// Last modified: 2017-08-05 09:20
// Filename: solution.cpp
// Description:
class Solution {
public:
    string predictPartyVictory(string senate) {
        int dcnt = 0, rcnt = 0;
        for(char c: senate)
            if(c == 'R')
                rcnt++;
            else
                dcnt++;
        int i = 0, size = senate.length();
        int not_alive[size] = {0};
        int ddie = 0, rdie = 0;
        while(dcnt && rcnt)
        {
            if(senate[i] == 'R')
            {
                if(rdie && not_alive[i] == 0)
                {
                    rdie--;
                    rcnt--;
                    not_alive[i] = 1;
                }
                else if(not_alive[i] == 0)
                    ddie++;
            }
            else
            {
                if(ddie && not_alive[i] == 0)
                {
                    ddie--;
                    dcnt--;
                    not_alive[i] = 1;
                }
                else if(not_alive[i] == 0)
                    rdie++;
            }
            i = (i + 1) % size;
        }
        return dcnt == 0? "Radiant": "Dire";
    }
};
