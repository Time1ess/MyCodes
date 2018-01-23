/* 题目描述:
 * 给定一个只包含[,{,(,),},]的字符串, 允许两种操作:
 * 1. 删除某个字符
 * 2. 转置为对应字符, 如 [ <-> ], ( <-> )
 * 求最长括号匹配字符串。
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


class Solution
{
public:
    bool is_left(char c)
    {
        if(c == '[' || c == '(' || c == '{')
            return true;
        return false;
    }
    char transpose(char c)
    {
        static unordered_map<char, char> mappings = {
            {'[', ']'}, {']', '['}, {'{', '}'}, {'}', '{'},
            {'(', ')'}, {')', '('}};
        return mappings[c];
    }
    char to_left(char c)
    {
        return is_left(c) ? c : transpose(c);
    }
    char to_right(char c)
    {
        return !is_left(c) ? c : transpose(c);
    }
    string dfs(string &s, vector<vector<bool>> &visited, vector<vector<string>> &dp, int i, int j)
    {
        if(visited[i][j])
            return dp[i][j];
        char ci = s[i], cj = s[j];
        ci = to_left(ci);
        cj = to_left(cj);
        if(i == j)
        {
            visited[i][j] = true;
            return dp[i][j];
        }
        else if(i + 1 == j)
        {
            if(ci == cj)
            {
                dp[i][j].push_back(to_left(ci));
                dp[i][j].push_back(to_right(cj));
            }
            visited[i][j] = true;
            return dp[i][j];
        }
        string tmp = dfs(s, visited, dp, i + 1, j);
        string ans = dfs(s, visited, dp, i, j - 1);
        ans = tmp.length() > ans.length() ? tmp : ans;
        if(ci == cj)
        {
            tmp = "";
            tmp.push_back(to_left(ci));
            tmp += dfs(s, visited, dp, i + 1, j - 1);
            tmp.push_back(to_right(cj));
            ans = tmp.length() > ans.length() ? tmp : ans;
        }
        dp[i][j] = ans;
        visited[i][j] = true;
        return dp[i][j];
    }
    string longest_pair_match_string(string s)
    {
        int length = s.length();
        vector<vector<bool>> visited(length, vector<bool>(length, false));
        vector<vector<string>> dp(length, vector<string>(length, ""));
        return dfs(s, visited, dp, 0, length - 1);
    }
};


int main()
{
    string s = "({[]})";  // ({[]})
    string s2 = "{([)}"; // {()}
    string s3 = "](][({]())])[{{](}{[{(]]{{(}{}]{](]{[)](";
    string s4 = "[}){([}}][{]{[]]{(({}]]})([{[()})]}]){[}{)))]{(((){]}[())([]]{)[[{)(][[)){){]{){](()[](((]{){})}[[}[";
    Solution sol;
    string src = s;
    string res = sol.longest_pair_match_string(src);
    cout<<res<<" "<<src.length()<<" "<<res.length()<<endl;
    src = s2;
    res = sol.longest_pair_match_string(src);
    cout<<res<<" "<<src.length()<<" "<<res.length()<<endl;
    src = s3;
    res = sol.longest_pair_match_string(src);
    cout<<res<<" "<<src.length()<<" "<<res.length()<<endl;
    src = s4;
    res = sol.longest_pair_match_string(src);
    cout<<res<<" "<<src.length()<<" "<<res.length()<<endl;
    return 0;
}
