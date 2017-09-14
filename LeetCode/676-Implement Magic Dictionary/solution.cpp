// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-14 08:39
// Last modified: 2017-09-14 08:39
// Filename: solution.cpp
// Description:
class MagicDictionary {
public:
    /** Initialize your data structure here. */
    MagicDictionary() {
        
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {  // O(n*len(s))
        char c;
        for(auto word: dict)
        {
            m[word] = 1;
            for(int i = 0; i < word.length(); i++)
            {
                c = word[i];
                word[i] = '*';
                m[word] += 1;
                word[i] = c;
            }
        }
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {  // O(len(s))
        char c;
        string t = word;
        for(int i = 0; i < t.length(); i++)
        {
            c = t[i];
            t[i] = '*';
            auto tar = m.find(t);
            if(tar != m.end() && (tar->second > 1 || m.find(word) == m.end()))
                return true;
            t[i] = c;
        }
        return false;
    }
private:
    unordered_map<string, int> m;
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary obj = new MagicDictionary();
 * obj.buildDict(dict);
 * bool param_2 = obj.search(word);
 */
