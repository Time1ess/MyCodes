/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head)
            return NULL;
        else if(head->next == NULL)
        {
            TreeNode *node = new TreeNode(head->val);
            return node;
        }
        int cnt = 0;
        ListNode *tmp = head;
        while(tmp)
        {
            cnt++;
            tmp = tmp->next;
        }
        tmp = head;
        ListNode *head2 = tmp->next;
        for(int i = 1; i < cnt / 2; i++)
        {
            tmp = tmp->next;
            head2 = head2->next;
        }
        tmp->next = NULL;
        TreeNode* root = new TreeNode(head2->val);
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(head2->next);
        return root;
    }
};
