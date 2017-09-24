// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-24 11:31
// Last modified: 2017-09-24 11:31
// Filename: solution.cpp
// Description:
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int size = strs.size();
        if(size == 0)
            return "";
        else if(size == 1)
            return strs[0];
        string ans;
        for(int i = 0; i < strs[0].length(); i++)
        {
            char common = strs[0][i];
            int j;
            for(j = 1; j < size; j++)
                if(i >= strs[j].length()|| common != strs[j][i])
                    break;
            if(j == size)
                ans.append(1, common);
            else
                break;
        }
        return ans;
    }
};
