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
    ListNode* merge(ListNode* head1, int n, ListNode* head2, int m)
    {
        if(n == 0)
            return head2;
        else if(m == 0)
            return head1;
        ListNode new_head(0);
        ListNode *tail = NULL;
        while(head1 || head2)
        {
            ListNode *next;
            if(!head2 || (head1 && head1->val < head2->val))
            {
                next = head1;
                head1 = head1->next;
            }
            else
            {
                next = head2;
                head2 = head2->next;
            }
            next->next = NULL;
            if(tail)
            {
                tail->next = next;
                tail = tail->next;
            }
            else
            {
                new_head.next = next;
                tail = next;
            }
        }
        return new_head.next;
    }
    ListNode* mergeSort(ListNode* head, int n)
    {
        if(n == 0 || n == 1)
            return head;
        ListNode* head2 = head;
        ListNode* pre = NULL;
        for(int i = 0; i < n / 2; i++)
        {
            pre = head2;
            head2 = head2->next;
        }
        pre->next = NULL;
        head = mergeSort(head, n / 2);
        head2 = mergeSort(head2, n - n / 2);
        return merge(head, n / 2, head2, n - n / 2);
    }
    ListNode* sortList(ListNode* head) {
        if(!head || head->next == NULL)
            return head;
        int n = 0;
        ListNode* tmp = head;
        while(tmp)
        {
            n++;
            tmp = tmp->next;
        }
        return mergeSort(head, n);
    }
};
