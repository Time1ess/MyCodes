// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-23 10:02
// Last modified: 2017-08-23 10:02
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool isValid(string s) {
        stack<char> match_stack;
        char matchings[256];
        matchings[')'] = '(';
        matchings[']'] = '[';
        matchings['}'] = '{';
        for(auto ch: s)
        {
            if(ch == '(' || ch == '[' || ch == '{')
                match_stack.push(ch);
            else if(!match_stack.empty() && match_stack.top() == matchings[ch])
                match_stack.pop();
            else
                return false;
        }
        return match_stack.empty();
    }
};
