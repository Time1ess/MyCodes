struct TrieNode {
    bool end;
    TrieNode *nodes[26];
    TrieNode(){
        end = false;
        for(int i = 0; i < 26; i++)
            nodes[i] = NULL;
    }
};

class Trie {
private:
    TrieNode root;
public:
    Trie() {
        // do intialization if necessary
    }

    /*
     * @param word: a word
     * @return: nothing
     */
    void insert(string &word) {
        // write your code here
        TrieNode *tmp = &root;
        for(auto ch: word)
        {
            if(tmp->nodes[ch-'a'] == NULL)
                tmp->nodes[ch-'a'] = new TrieNode();
            tmp = tmp->nodes[ch-'a'];
        }
        tmp->end = true;
    }

    /*
     * @param word: A string
     * @return: if the word is in the trie.
     */
    bool search(string &word) {
        // write your code here
        TrieNode *tmp = &root;
        for(auto ch: word)
        {
            if(tmp->nodes[ch-'a'] == NULL)
                return false;
            tmp = tmp->nodes[ch-'a'];
        }
        return tmp->end;
    }

    /*
     * @param prefix: A string
     * @return: if there is any word in the trie that starts with the given prefix.
     */
    bool startsWith(string &prefix) {
        // write your code here
        if(!prefix.length())
            return true;
        TrieNode *tmp = &root;
        for(auto ch: prefix)
        {
            if(tmp->nodes[ch-'a'] == NULL)
                return false;
            tmp = tmp->nodes[ch-'a'];
        }
        return true;
    }
};
