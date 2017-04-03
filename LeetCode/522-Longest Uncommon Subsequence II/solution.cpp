// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-03 10:33
// Last modified: 2017-04-03 10:33
// Filename: solution.cpp
// Description:
bool cmp(const pair<string, int> &a, const pair<string, int> &b)
{
    return a.second > b.second;
}
class Solution {
public:
    bool check_sub(string ss, string sub)
    {
        int s1 = ss.length(), s2 = sub.length();
        int i = 0, j = 0;
        while(i < s1 && j < s2)
        {
            if(ss[i] == sub[j])
                j++;
            i++;
        }
        if(j == s2)
            return true;
        return false;
        
    }
    int findLUSlength(vector<string>& strs) {
        if(strs.size() == 0)
            return 0;
        vector<pair<string, int>> ss;
        for(auto x: strs)
            ss.push_back(make_pair(x, x.length()));
        sort(ss.begin(), ss.end(), cmp);
        ss.push_back(make_pair("", 0));
        for(int i = 0; i < ss.size() - 1; i++)
        {
            for(int j = 0; j < ss.size(); j++)
            {
                if(ss[i].second > ss[j].second)
                    return ss[i].second;
                if(i != j && check_sub(ss[j].first, ss[i].first))
                    break;
            }
        }
        return -1;
    }
};
