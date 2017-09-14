// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-14 08:47
// Last modified: 2017-09-14 08:47
// Filename: solution2.cpp
// Description:
class MagicDictionary {
public:
    /** Initialize your data structure here. */
    MagicDictionary() {
        
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        for(auto x: dict)
            v.push_back(x);
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        for(int i = 0; i < v.size(); i++)
            if(is_magic(v[i], word))
                return true;
        return false;
    }
    
    bool is_magic(string &s1, string &s2)
    {
        if(s1.length() != s2.length())
            return false;
        int diff_cnt = 0;
        for(int i = 0; i < s1.length(); i++)
        {
            if(s1[i] != s2[i])
                diff_cnt++;
            if(diff_cnt == 2)
                return false;
        }
        return diff_cnt == 1;
    }

private:
    vector<string> v;
};


/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary obj = new MagicDictionary();
 * obj.buildDict(dict);
 * bool param_2 = obj.search(word);
 */
