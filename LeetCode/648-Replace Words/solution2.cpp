// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-24 14:47
// Last modified: 2017-07-24 14:47
// Filename: solution2.cpp
// Description:
class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        set<string> s;
        set<string> has_prefix = {""};
        int has_next[110][26] = {{0}};
        int word_length;
        for(auto word: dict)
        {
            s.insert(word);
            for(int i = 1; i <= word.length(); i++)
                has_prefix.insert(word.substr(0, i));
        }
        string ans = "";
        int i = 0, k;
        bool replace;
        string tmp;
        while(i < sentence.length())
        {
            k = i;
            tmp = "";
            replace = true;
            while(k < sentence.length() && sentence[k] != ' ')
            {
                if(has_prefix.find(tmp) == has_prefix.end())
                {
                    replace = false;
                    break;
                }
                tmp.append(1, sentence[k]);
                if(s.find(tmp) != s.end())
                    break;
                k++;
            }
            ans.append(" ");
            if(replace == true)
            {
                ans.append(tmp);
                while(k < sentence.length() && sentence[k++] != ' ');
            }
            else
            {
                while(k < sentence.length() && sentence[k] != ' ')
                {
                    tmp.append(1, sentence[k]);
                    k++;
                }
                ans.append(tmp);
                k++;
            }
            i = k;
        }
        return ans.substr(1);
    }
};
