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
    ListNode* oddEvenList(ListNode* head) {
        if(!head || head->next == NULL || head->next->next == NULL)
            return head;
        ListNode odd_list(0), even_list(0);
        ListNode *odd_tail = NULL, *even_tail = NULL;
        bool odd = true;
        while(head)
        {
            ListNode *next = head->next;
            head->next = NULL;
            if(odd)
            {
                if(odd_list.next == NULL)
                {
                    odd_list.next = head;
                    odd_tail = head;
                }
                else
                {
                    odd_tail->next = head;
                    odd_tail = odd_tail->next;
                }
            }
            else
            {
                if(even_list.next == NULL)
                {
                    even_list.next = head;
                    even_tail = head;
                }
                else
                {
                    even_tail->next = head;
                    even_tail = even_tail->next;
                }
            }
            head = next;
            odd = !odd;
        }
        odd_tail->next = even_list.next;
        return odd_list.next;
    }
};
