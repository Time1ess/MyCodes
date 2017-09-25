// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-25 08:43
// Last modified: 2017-09-25 08:43
// Filename: solution.cpp
// Description:
class Solution {
public:
    int calPoints(vector<string>& ops) {
        stack<int> scores;
        int last, last_but_one, ans = 0; 
        for(auto op: ops)
        {
            if(op == "+")
            {
                last = scores.top();
                scores.pop();
                last_but_one = scores.top();
                scores.push(last);
                scores.push(last+last_but_one);
            }
            else if(op == "C")
                scores.pop();
            else if(op == "D")
            {
                last = scores.top();
                scores.push(last * 2);
            }
            else
                scores.push(stoi(op));
        }
        while(!scores.empty())
        {
            ans += scores.top();
            scores.pop();
        }
        return ans;
    }
};
