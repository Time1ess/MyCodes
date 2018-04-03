struct TrieNode
{
    int val;
    int path_sum;
    bool end;
    TrieNode *next[128];
    TrieNode()
    {
        end = false;
        val = 0;
        path_sum = 0;
        for(int i = 0; i < 128; i++)
            next[i] = NULL;
    }
};

class MapSum {
private:
    TrieNode *root;
public:
    /** Initialize your data structure here. */
    MapSum() {
        root = new TrieNode();
    }
    
    void insert(string key, int val) {
        TrieNode *node = root;
        for(auto c: key)
        {
            if(node->next[c] == NULL)
                node->next[c] = new TrieNode();
            node = node->next[c];
        }
        int diff = val;
        if(node->end == true)
            diff -= node->val;
        node->val = val;
        node->end = true;
        node = root;
        for(auto c: key)
        {
            node->path_sum += diff;
            node = node->next[c];
        }
        node->path_sum += diff;
    }
    
    int sum(string prefix) {
        TrieNode *node = root;
        for(auto c: prefix)
        {
            if(node->next[c] == NULL)
                return 0;
            node = node->next[c];
        }
        return node->path_sum;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum obj = new MapSum();
 * obj.insert(key,val);
 * int param_2 = obj.sum(prefix);
 */
