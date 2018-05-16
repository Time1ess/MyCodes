/**
 * Definition of ListNode
 * class ListNode {
 * public:
 *     int val;
 *     ListNode *next;
 *     ListNode(int val) {
 *         this->val = val;
 *         this->next = NULL;
 *     }
 * }
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
private:
    ListNode *head;
    TreeNode* sortedListToBST(int n)
    {
        if(n == 0)
            return NULL;
        TreeNode* root = new TreeNode(0);
        root->left = sortedListToBST(n / 2);
        root->val = head->val;
        head = head->next;
        root->right = sortedListToBST(n - n / 2 - 1);
        return root;
    }
public:
    /*
     * @param head: The first node of linked list.
     * @return: a tree node
     */
    int get_list_length(ListNode *head)
    {
        int n = 0;
        while(head)
        {
            n++;
            head = head->next;
        }
        return n;
    }
    TreeNode * sortedListToBST(ListNode * head) {
        // write your code here
        if(!head)
            return NULL;
        this->head = head;
        return sortedListToBST(get_list_length(head));
    }
};
