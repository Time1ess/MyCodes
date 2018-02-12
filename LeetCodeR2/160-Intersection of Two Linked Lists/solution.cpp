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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *tmp;
        int len1 = 0, len2 = 0;
        tmp = headA;
        while(tmp)
        {
            len1++;
            tmp = tmp->next;
        }
        tmp = headB;
        while(tmp)
        {
            len2++;
            tmp = tmp->next;
        }
        if(len1 > len2)
            for(int i = 0; i < len1 - len2; i++)
                headA = headA->next;
        else if(len2 > len1)
            for(int i = 0; i < len2 - len1; i++)
                headB = headB->next;
        while(headA != NULL && headB != NULL)
        {
            if(headA == headB)
                return headA;
            headA = headA->next;
            headB = headB->next;
        }
        return NULL;
    }
};
