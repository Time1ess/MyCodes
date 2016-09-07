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
        if(head==NULL||head->next==NULL)
        return false;
        ListNode *slower,*faster;
        slower=faster=head;
        while(faster->next&&faster->next->next)
        {
            slower=slower->next;
            faster=faster->next->next;
            if(slower==faster)
            return true;
        }
        return false;
    }
};
