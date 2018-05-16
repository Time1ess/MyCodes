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
public:
    /*
     * @param head: The first node of linked list.
     * @return: a tree node
     */
    TreeNode* sortedListToBST(ListNode *head, int s, int e)
    {
        if(s >= e)
            return NULL;
        int m = s + (e - s) / 2;
        ListNode *pre, *cur = head;
        for(int i = s; i < m; i++)
            cur = cur->next;
        TreeNode* root = new TreeNode(cur->val);
        root->left = sortedListToBST(head, s, m);
        root->right = sortedListToBST(cur->next, m + 1, e);
        return root;
    }
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
        return sortedListToBST(head, 0, get_list_length(head));
    }
};
