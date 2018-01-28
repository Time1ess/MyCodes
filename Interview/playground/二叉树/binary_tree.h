#include <vector>
#include <string>


struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v)
    {
        val = v;
    }
};


TreeNode* build_tree(const std::vector<std::string> &s, int &index);
TreeNode* build_tree(const std::vector<std::string> &s);
TreeNode* build_tree();
