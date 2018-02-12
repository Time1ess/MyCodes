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
    bool isPalindrome(ListNode* head, int k, ListNode** other)
    {
        bool is_palindrome = false;
        if(k == 0)
            is_palindrome = head->val == (*other)->val;
        else
            is_palindrome = isPalindrome(head->next, k - 1, other) && head->val == (*other)->val;
        *other = (*other)->next;
        return is_palindrome;
    }
    bool isPalindrome(ListNode* head) {
        if(!head || head->next == NULL)
            return true;
        int cnt = 0;
        ListNode* tmp = head;
        while(tmp)
        {
            cnt++;
            tmp = tmp->next;
        }
        ListNode** other;
        tmp = head;
        for(int i = 0; i < cnt / 2; i++)
            tmp = tmp->next;
        if(cnt & 0x1 == 1)
            other = &(tmp->next);
        else
            other = &tmp;
        return isPalindrome(head, cnt / 2 - 1, other);
    }
};
