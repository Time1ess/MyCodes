// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-04 09:57
// Last modified: 2017-05-04 09:57
// Filename: solution.cpp
// Description:
struct Indent
{
    int ind;
    int len;
    Indent()
    {
        ind = 0;
        len = 0;
    }
    Indent(int i, int l):ind(i), len(l){};
};

class Solution {
public:
    int lengthLongestPath(string input) {
        int last_indent = -1;
        stack<Indent> indents;
        indents.push(Indent(0, 0));
        int longest = 0, cur = 0, len = 0, ind = 0;
        bool file = false;
        input.append("\n");
        for(int i = 0; i < input.size(); i++)
        {
            if(input[i] == '\t')
                ind++;
            else if(input[i] == '\n')
            {
                if(ind <= indents.top().ind)  // Same or Higher level
                {
                    while(!indents.empty() && ind <= indents.top().ind)
                    {
                        cur = cur - indents.top().len - (ind == indents.top().ind ? 0 : 1);
                        indents.pop();
                    }
                    cur += len;
                    indents.push(Indent(ind, len));
                }
                else if(ind > indents.top().ind)  // Sub level
                {
                    indents.push(Indent(ind, len));
                    cur += len + 1;
                }
                if(file)
                    longest = max(longest, cur);
                ind = 0;
                len = 0;
                file = false;
            }
            else if(input[i] == '.')
            {
                len++;
                file = true;
            }
            else
                len++;
        }
        return longest;
    }
};
