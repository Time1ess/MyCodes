class MagicDictionary {
private:
    unordered_set<string> words;
    unordered_map<string, int> cnts;
public:
    /** Initialize your data structure here. */
    MagicDictionary() {
        
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        for(auto s: dict)
        {
            words.insert(s);
            int len = s.length();
            for(int i = 0; i < len; i++)
            {
                char tmp = s[i];
                s[i] = '*';
                cnts[s]++;
                s[i] = tmp;
            }
        }
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        string original = word;
        int len = word.length();
        for(int i = 0; i < len; i++)
        {
            char tmp = word[i];
            word[i] = '*';
            if(cnts[word] > 1 || (cnts[word] == 1 && words.find(original) == words.end()))
                return true;
            word[i] = tmp;
        }
        return false;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary obj = new MagicDictionary();
 * obj.buildDict(dict);
 * bool param_2 = obj.search(word);
 */
