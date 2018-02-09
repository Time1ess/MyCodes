#include <vector>
#include <string>
#include "binary_tree.h"


TreeNode* build_tree(const std::vector<std::string> &s, int &index)
{
    int size = s.size();
    if(index >= size)
        return NULL;
    if(s[index] == "#")
    {
        index++;
        return NULL;
    }
    TreeNode *root = new TreeNode(stoi(s[index]));
    index++;
    root->left = build_tree(s, index);
    root->right = build_tree(s, index);
    return root;
}


TreeNode* build_tree(const std::vector<std::string> &s)
{
    int index = 0;
    return build_tree(s, index);
}

TreeNode* build_tree()
{
    std::vector<std::string> s{"1","2","4","#","#","#","3","5"};
    //std::vector<std::string> s{"1","2","#","#","3"};
    return build_tree(s);
}
