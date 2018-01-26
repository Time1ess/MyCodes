#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

class Solution {
public:
    void Serialize(string &s, TreeNode *root)
    {
        if(!root)
        {
            s.append("#,");
            return;
        }
        s.append(to_string(root->val)+",");
        Serialize(s, root->left);
        Serialize(s, root->right);
    }
    char* Serialize(TreeNode *root) {
        if(!root)
            return NULL;
        string s = "";
        Serialize(s, root);
        char* p = (char*)malloc(sizeof(char) * s.length());
        memcpy(p, s.c_str(), s.length());
        return p;
    }
    TreeNode* Deserialize(char *str, char **p)
    {
    	if(!str || *str == '\0')
            return NULL;
        if(*str == '#')
        {
            (*p)++;
            (*p)++;
            return NULL;
        }
        while(**p != ',')
            (*p)++;
        **p = '\0';
        (*p)++;
        TreeNode *node = new TreeNode(atoi(str));
        node->left = Deserialize(*p, p);
        node->right = Deserialize(*p, p);
        return node;
    }
    TreeNode* Deserialize(char *str) {
        if(!str)
            return NULL;
		char *p = str;
        return Deserialize(p, &p);
    }
};


int main()
{
    char s[] = "11,22,5,#,6,#,#,#,33,#,#,";
    Solution sol;
    TreeNode *root = sol.Deserialize(s);
    char *ss = sol.Serialize(root);
    cout<<"Output: "<<ss<<endl;
    return 0;
}
