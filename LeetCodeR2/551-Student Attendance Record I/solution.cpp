class Solution {
public:
    bool checkRecord(string s) {
        int absents = 0, lates = 0;
        for(int i = 0; i < s.length(); i++)
        {
            if(s[i] == 'L')
                lates++;
            else
                lates = 0;
            if(s[i] == 'A')
                absents++;
            if(lates == 3 || absents == 2)
                return false;
        }
        return true;
    }
};
