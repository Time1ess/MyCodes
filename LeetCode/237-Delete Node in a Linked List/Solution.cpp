/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        if(node==NULL)
        return;
        if(node->next->next==NULL)
        {
            ListNode* p=node->next;
            node->val=p->val;
            node->next=NULL;
            delete p;
        }
        else
        {
        while(node->next->next)
        {
            node->val=node->next->val;
            node=node->next;
        }
        ListNode* p=node->next;
        node->val=p->val;
        node->next=NULL;
        delete p;
        }
    }
};
