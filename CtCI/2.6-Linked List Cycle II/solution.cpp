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
    ListNode *detectCycle(ListNode *head) {
        if(!head)
            return NULL;
        ListNode *fast = head, *slow = head;
        while(fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow) {
                ListNode* entry = head;
                while(entry != slow) {
                    slow = slow->next;
                    entry = entry->next;
                }
                return entry;
            }
        }
        return NULL;
    }
};
