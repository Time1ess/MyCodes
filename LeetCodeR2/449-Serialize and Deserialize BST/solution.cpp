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
        if(root == NULL)
            return "#,";
        return to_string(root->val) + "," + serialize(root->left) + serialize(root->right);
    }
    
    TreeNode* deserialize(string &data, int &idx, int n)
    {
        if(idx < n && data[idx] == '#')  // Null
        {
            idx += 2;
            return NULL;
        }
        int s = idx;
        while(s < n && data[s] != ',')
            s++;
        TreeNode *root = new TreeNode(stoi(data.substr(idx, s - idx)));
        idx = s + 1;
        root->left = deserialize(data, idx, n);
        root->right = deserialize(data, idx, n);
        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int idx = 0;
        return deserialize(data, idx, data.length());
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
