// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-20 15:28
// Last modified: 2017-10-20 15:28
// Filename: solution.cpp
// Description:
struct TrieNode
{
    bool end;
    TrieNode* next[26];
    TrieNode()
    {
        end = false;
        for(int i = 0; i < 26; i++)
            next[i] = NULL;
    };
};

class Trie {
private:
    TrieNode root;
    
    TrieNode* search_node(string &word)
    {
        TrieNode *tmp = &root;
        for(auto ch: word)
        {
            if(tmp->next[ch - 'a'] == NULL)
                return NULL;
            tmp = tmp->next[ch - 'a'];
        }
        return tmp;
    }
public:
    /** Initialize your data structure here. */
    Trie() {
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode *tmp = &root;
        int len = word.length();
        for(int i = 0; i < len; i++)
        {
            if(tmp->next[word[i] - 'a'] == NULL)
                tmp->next[word[i] - 'a'] = new TrieNode();
            tmp = tmp->next[word[i] - 'a'];
            if(i == len - 1)
                tmp->end = true;
        }
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* tmp = search_node(word);
        return tmp && tmp->end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return search_node(prefix) != NULL;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */
