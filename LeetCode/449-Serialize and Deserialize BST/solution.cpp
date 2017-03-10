// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-10 21:18
// Last modified: 2017-03-10 21:18
// Filename: solution.cpp
// Description:
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
            return "# ";
        TreeNode *t;
        string s = to_string(root->val)+" ";
        s += serialize(root->left);
        s += serialize(root->right);
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == "")
            return NULL;
        int len = data.length();
        queue<string> q;
        stringstream ss(data);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        for(auto it=begin; it != end; it++)
        {
            q.push(*it);
        }
        return reconstruct(q);
    }
    TreeNode* reconstruct(queue<string> &q)
    {
        string s = q.front();
        q.pop();
        if(s == "#")
            return NULL;
        TreeNode *root = new TreeNode(stoi(s));
        root->left = reconstruct(q);
        root->right = reconstruct(q);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
