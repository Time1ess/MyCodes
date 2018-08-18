struct TrieNode {
    bool end;
    TrieNode* next[26];
    TrieNode() {
        end = false;
        for (int i = 0; i < 26; i++) {
            next[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode root;
public:
    /** Initialize your data structure here. */
    Trie() {
        
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* node = &root;
        for (auto ch: word) {
            if (node->next[ch-'a'] == nullptr) {
                node->next[ch-'a'] = new TrieNode();
            }
            node = node->next[ch-'a'];
        }
        node->end = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* node = &root;
        for (auto ch: word) {
            if (node->next[ch-'a'] == nullptr) {
                return false;
            }
            node = node->next[ch-'a'];
        }
        return node->end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* node = &root;
        for (auto ch: prefix) {
            if (node->next[ch-'a'] == nullptr) {
                return false;
            }
            node = node->next[ch-'a'];
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
