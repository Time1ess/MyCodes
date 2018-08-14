/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) {
            return "#,";
        }
        return to_string(root->val) + "," + serialize(root->left) + serialize(root->right);
    }
    
    int read_value(string& data, int& idx, int n) {
        if (idx >= n) {
            return 0;
        }
        bool neg = false;
        if (data[idx] == '-') {
            neg = true;
            idx++;
        }
        int val = 0;
        while (idx < n && data[idx] != ',') {
            val = val * 10 + data[idx] - '0';
            idx++;
        }
        idx++;
        return neg ? (-1 * val) : val;
    }
    
    TreeNode* deserialize(string& data, int& idx, int n) {
        if (idx >= n || data[idx] == '#') {
            idx += 2;
            return NULL;
        }
        TreeNode* root = new TreeNode(read_value(data, idx, n));
        root->left = deserialize(data, idx, n);
        root->right = deserialize(data, idx, n);
        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int n = data.length();
        int idx = 0;
        return deserialize(data, idx, n);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
