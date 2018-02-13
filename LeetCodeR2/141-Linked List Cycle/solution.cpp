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
    bool hasCycle(ListNode *head) {
        if(!head)
            return NULL;
        ListNode *fast = head;
        while(fast->next && fast->next->next)
        {
            head = head->next;
            fast = fast->next->next;
            if(head == fast)
                return true;
        }
        return false;
    }
};
