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
private:
    ListNode* reverse_list(ListNode *head, ListNode **tail)
    {
        if(!head)
            return NULL;
        if(head->next == NULL)
        {
            *tail = head;
            return head;
        }
        ListNode *new_head = reverse_list(head->next, tail);
        head->next = NULL;
        (*tail)->next = head;
        *tail = head;
        return new_head;
    }
public:
    /**
     * @param head: The head of linked list.
     * @return: nothing
     */
    int get_list_length(ListNode *head)
    {
        int n = 0;
        while(head)
        {
            head = head->next;
            n++;
        }
        return n;
    }
    ListNode* split_list(ListNode *head, int n)
    {
        int m = n / 2;
        ListNode *pre, *cur = head;
        for(int i = 0; i <= m; i++)
        {
            pre = cur;
            cur = cur->next;
        }
        pre->next = NULL;
        return cur;
    }
    ListNode* reverse_list(ListNode *head)
    {
        ListNode *tail = NULL;
        return reverse_list(head, &tail);
    }
    void merge_list(ListNode **head, ListNode **second_head)
    {
        while(*head && *second_head)
        {
            ListNode *tmp_node = (*head)->next;
            ListNode *tmp_second_node = (*second_head)->next;
            (*head)->next = *second_head;
            (*second_head)->next = tmp_node;
            *head = tmp_node;
            *second_head = tmp_second_node;
        }
    }
    void reorderList(ListNode * head) {
        // write your code here
        if(!head)
            return;
        int n = get_list_length(head);
        ListNode *second_head = split_list(head, n);
        second_head = reverse_list(second_head);
        merge_list(&head, &second_head);
    }
};
