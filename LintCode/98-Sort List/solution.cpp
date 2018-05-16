/**
 * Definition of singly-linked-list:
 * class ListNode {
 * public:
 *     int val;
 *     ListNode *next;
 *     ListNode(int val) {
 *        this->val = val;
 *        this->next = NULL;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param head: The head of linked list.
     * @return: You should return the head of the sorted linked list, using constant space complexity.
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
    ListNode *merge_sort(ListNode *head, int s, int e)
    {
        if(!head || s >= e)
            return NULL;
        if(s + 1 == e)
        {
            head->next = NULL;
            return head;
        }
        int m = s + (e - s) / 2;
        ListNode *pre, *second_head = head;
        for(int i = s; i < m; i++)
        {
            pre = second_head;
            second_head = second_head->next;
        }
        pre->next = NULL;
        return merge(merge_sort(head, s, m), merge_sort(second_head, m, e));
    }
    ListNode* merge(ListNode *h1, ListNode *h2)
    {
        ListNode new_head(0);
        ListNode *new_tail = &new_head;
        while(h1 && h2)
        {
            if(h1->val < h2->val)
            {
                new_tail->next = h1;
                h1 = h1->next;
            }
            else
            {
                new_tail->next = h2;
                h2 = h2->next;
            }
            new_tail = new_tail->next;
            new_tail->next = NULL;
        }
        if(h1)
            new_tail->next = h1;
        else
            new_tail->next = h2;
        return new_head.next;
    }
    ListNode * sortList(ListNode * head) {
        // write your code here
        if(!head)
            return head;
        int n = get_list_length(head);
        return merge_sort(head, 0, n);
    }
};
