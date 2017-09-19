// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-19 09:00
// Last modified: 2017-09-19 09:00
// Filename: solution.cpp
// Description:
struct TrieNode
{
    int val;
    TrieNode* next[128];
    TrieNode()
    {
        val = 0;
        for(int i = 0; i < 128; i++)
            next[i] = NULL;
    }
    TrieNode(int value)
    {
        val = value;
        for(int i = 0; i < 128; i++)
            next[i] = NULL;
    }
};
class MapSum {
private:
    TrieNode head;
    unordered_map<string, int> show;
    
public:
    /** Initialize your data structure here. */
    MapSum() {
        
    }
    
    void insert(string key, int val) {
        TrieNode *t = &head;
        int dup_val = show[key];
        t->val += val - dup_val;
        for(int i = 0; i < key.length(); i++)
        {
            if(t->next[key[i]] == NULL)
                t->next[key[i]] = new TrieNode(0);
            t = t->next[key[i]];
            t->val += val - dup_val;
        }
        show[key] = val;
    }
    
    int sum(string prefix) {
        TrieNode *t = &head;
        for(int i = 0; i < prefix.length(); i++)
        {
            if(t->next[prefix[i]] == NULL)
                return 0;
            t = t->next[prefix[i]];
        }
        return t->val;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum obj = new MapSum();
 * obj.insert(key,val);
 * int param_2 = obj.sum(prefix);
 */
