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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2, int len1, int len2, bool &adding)
    {
        ListNode *tail, *new_node;
        if(len1 == 0 || len2 == 0)
        {
            adding = false;
            return NULL;
        }
        else if(len1 == len2)
        {
            tail = addTwoNumbers(l1->next, l2->next, len1-1, len2-1, adding);
            new_node = new ListNode(l1->val + l2->val + (adding ? 1 : 0));
        }
        else if(len1 > len2)
        {
            tail = addTwoNumbers(l1->next, l2, len1-1, len2, adding);
            new_node = new ListNode(l1->val + (adding ? 1 : 0));
        }
        else
        {
            tail = addTwoNumbers(l1, l2->next, len1, len2-1, adding);
            new_node = new ListNode(l2->val + (adding ? 1 : 0));
        }
        adding = false;
        if(new_node->val >= 10)
        {
            new_node->val %= 10;
            adding = true;
        }
        new_node->next = tail;
        return new_node;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(l1 == NULL)
            return l2;
        else if(l2 == NULL)
            return l1;
        int len1 = 0, len2 = 0;
        ListNode *t = l1;
        while(t)
        {
            len1++;
            t = t->next;
        }
        t = l2;
        while(t)
        {
            len2++;
            t = t->next;
        }
        bool adding = false;
        ListNode *ans = addTwoNumbers(l1, l2, len1, len2, adding);
        if(adding)
        {
            ListNode* adding_node = new ListNode(1);
            adding_node->next = ans;
            ans = adding_node;
        }
        return ans;
    }
};
