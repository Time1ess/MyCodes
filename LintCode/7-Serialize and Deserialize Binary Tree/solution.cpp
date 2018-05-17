/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */


class Solution {
public:
    /**
     * This method will be invoked first, you should design your own algorithm 
     * to serialize a binary tree which denote by a root node to a string which
     * can be easily deserialized by your own "deserialize" method later.
     */
    string serialize(TreeNode * root) {
        // write your code here
        if(!root)
            return "#,";
        string s = to_string(root->val) + ",";
        s = s + serialize(root->left) + serialize(root->right);
        return s;
    }

    /**
     * This method will be invoked second, the argument data is what exactly
     * you serialized at method "serialize", that means the data is not given by
     * system, it's given by your own serialize method. So the format of data is
     * designed by yourself, and deserialize it here as you serialize it in 
     * "serialize" method.
     */
    TreeNode* deserialize(string &data, int &idx, int n)
    {
        if(idx >= n)
            return NULL;
        if(data[idx] == '#')
        {
            idx += 2;
            return NULL;
        }
        int comma_idx = idx;
        while(comma_idx < n && data[comma_idx] != ',')
            comma_idx++;
        TreeNode* root = new TreeNode(stoi(data.substr(idx, comma_idx - idx)));
        idx = comma_idx + 1;
        root->left = deserialize(data, idx, n);
        root->right = deserialize(data, idx, n);
        return root;
    }
    TreeNode * deserialize(string &data) {
        // write your code here
        int n = data.length();
        int idx = 0;
        return deserialize(data, idx, n);
    }
};
