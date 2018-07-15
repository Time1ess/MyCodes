struct SuffixTreeNode {
    SuffixTreeNode* next[26];
    SuffixTreeNode() {
        for(int i = 0; i < 26; i++) {
            next[i] = NULL;
        }
    }
};

class Substr {
public:
    void insert_suffix_node(SuffixTreeNode* root, const string& str, int s, int e) {
        if(s == e) {
            return;
        }
        if(root->next[str[s]-'a'] == NULL) {
            root->next[str[s]-'a'] = new SuffixTreeNode();
        }
        insert_suffix_node(root->next[str[s]-'a'], str, s+1, e);
    }
    void construct_suffix_tree(SuffixTreeNode* root, const string& s) {
        int n = s.length();
        for(int i = n - 1; i >= 0; i--) {
            insert_suffix_node(root, s, i, n);
        }
    }
    bool is_substring(SuffixTreeNode* root, const string& str) {
        SuffixTreeNode* node = root;
        int n = str.length();
        for(int i = 0; i < n; i++) {
            if(node->next[str[i]-'a'] == NULL) {
                return false;
            }
            node = node->next[str[i]-'a'];
        }
        return true;
    }
    vector<bool> chkSubStr(vector<string> p, int n, string s) {
        // write code here
        SuffixTreeNode* root = new SuffixTreeNode();
        construct_suffix_tree(root, s);
        vector<bool> ans;
        for(auto x: p) {
            ans.push_back(is_substring(root, x));
        }
        return ans;
    }
};
