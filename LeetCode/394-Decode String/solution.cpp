// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-12 16:16
// Last modified: 2017-03-12 16:16
// Filename: solution.cpp
// Description:
class Solution {
public:
    string decodeString(string s) {
        stack<string> ss, sc;
        string ans = "", cnts = "", ts;
        int repeat;
        for(int i = 0; i < s.length(); i ++)
        {
            if(s[i] >= '0' && s[i] <= '9')
                cnts.append(1, s[i]);
            else if(s[i] == '[')
            {
                sc.push(cnts);
                ss.push(ans);
                ans = "";
                cnts = "";
            }
            else if(s[i] == ']')
            {
                repeat = stoi(sc.top());
                sc.pop();
                ts = ans;
                for(int k = 1; k < repeat; k++)
                    ans += ts;
                ans = ss.top() + ans;
                ss.pop();
            }
            else
                ans.append(1, s[i]);
        }
        return ans;
    }
};
