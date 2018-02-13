/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head)
            return head;
        RandomListNode *tmp = head;
        while(tmp)  // Duplicate nodes
        {
            RandomListNode *next = tmp->next;
            RandomListNode *dup = new RandomListNode(tmp->label);
            tmp->next = dup;
            dup->next = next;
            tmp = next;
        }
        tmp = head;
        while(tmp)  // Set random reference
        {
            RandomListNode *next = tmp->next;
            if(tmp->random)
                next->random = tmp->random->next;
            tmp = next->next;
        }
        RandomListNode new_head(0), *new_tail;
        tmp = head;
        while(tmp)  // Split duplicated nodes
        {
            RandomListNode *next = tmp->next;
            tmp->next = next->next;
            tmp = tmp->next;
            next->next = NULL;
            if(new_head.next)
            {
                new_tail->next = next;
                new_tail = next;
            }
            else
            {
                new_head.next = next;
                new_tail = next;
            }
        }
        return new_head.next;
    }
};
