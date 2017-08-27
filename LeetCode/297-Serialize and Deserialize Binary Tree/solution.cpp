// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-27 14:55
// Last modified: 2017-08-27 14:55
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
            return "#";
        return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int index = 0;
        return _deserialize(data, index);
    }
    TreeNode* _deserialize(string &data, int &index)
    {
        if(index == data.length())
            return NULL;
        else if(data[index] == '#')
        {
            index += 2;
            return NULL;
        }
        else
        {
            TreeNode *tmp = new TreeNode(parse_next_val(data, index));
            tmp->left = _deserialize(data, index);
            tmp->right = _deserialize(data, index);
            return tmp;
        }
    }
    int parse_next_val(string &data, int &index)
    {
        int end = index;
        while(data[++end] != ',');
        int val = stoi(data.substr(index, end - index));
        index = end + 1;
        return val;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
