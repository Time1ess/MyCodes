// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-08 17:15
// Last modified: 2017-05-08 17:15
// Filename: solution.cpp
// Description:
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
        ListNode *p, *p1, *p2, *same_start, *hl, *hs;
        int val = 0;
        int cnt_a = 0, cnt_b = 0;
        p = headA;
        while(p)
        {
            cnt_a ++;
            p = p->next;
        }
        p = headB;
        while(p)
        {
            cnt_b ++;
            p = p->next;
        }
        if(cnt_a == 0 || cnt_b == 0)
            return NULL;
        else if(cnt_a >= cnt_b)
        {
            hl = headA;
            hs = headB;
        }
        else if(cnt_a < cnt_b)
        {
            hl = headB;
            hs = headA;
            swap(cnt_a, cnt_b);
        }
        p1 = hl;
        p2 = hs;
        while(cnt_a > cnt_b)
        {
            p1 = p1->next;
            cnt_a--;
        }
        while(p1)
        {
            if(p1 == p2)
                return p1;
            p1 = p1->next;
            p2 = p2->next;
        }
        return NULL;
    }
};
