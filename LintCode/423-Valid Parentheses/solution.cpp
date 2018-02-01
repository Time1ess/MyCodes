class Solution {
public:
    /*
     * @param s: A string
     * @return: whether the string is a valid parentheses
     */
    bool isValidParentheses(string &s) {
        // write your code here
        stack<char> pairs;
        int size = s.length();
        for(int i = 0; i < size; i++)
        {
            if(s[i] == '(' || s[i] == '{' || s[i] == '[')
                pairs.push(s[i]);
            else
            {
                if(pairs.empty())
                    return false;
                char top = pairs.top();
                if((s[i] == ')' && top == '(')
                   || (s[i] == '}' && top == '{')
                   || (s[i] == ']' && top == '['))
                   pairs.pop();
                else
                    return false;
            }
        }
        return pairs.empty();
    }
};
