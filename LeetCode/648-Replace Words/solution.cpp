// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-24 14:33
// Last modified: 2017-07-24 14:33
// Filename: solution.cpp
// Description:
class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        set<string> s;
        for(auto word: dict)
            s.insert(word);
        string ans = "";
        int i = 0, k;
        string tmp;
        while(i < sentence.length())
        {
            k = i;
            tmp = "";
            while(k < sentence.length() && sentence[k] != ' ')
            {
                tmp.append(1, sentence[k]);
                if(s.find(tmp) != s.end())
                    break;
                k++;
            }
            ans.append(" ");
            ans.append(tmp);
            while(k < sentence.length() && sentence[k++] != ' ');
            i = k;
        }
        return ans.substr(1);
    }
};
