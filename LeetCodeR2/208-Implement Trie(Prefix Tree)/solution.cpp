struct TrieNode
{
    bool end;
    TrieNode *nexts[26];
    TrieNode()
    {
        end = false;
        for(int i = 0; i < 26; i++)
            nexts[i] = NULL;
    }
};

class Trie {
private:
    TrieNode *root;
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode *tmp = root;
        for(auto ch: word)
        {
            if(tmp->nexts[ch-'a'] == NULL)
                tmp->nexts[ch-'a'] = new TrieNode();
            tmp = tmp->nexts[ch-'a'];
        }
        tmp->end = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode *tmp = root;
        for(auto ch: word)
        {
            if(tmp->nexts[ch-'a'] == NULL)
                return false;
            tmp = tmp->nexts[ch-'a'];
        }
        return tmp->end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode *tmp = root;
        for(auto ch: prefix)
        {
            if(tmp->nexts[ch-'a'] == NULL)
                return false;
            tmp = tmp->nexts[ch-'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */
