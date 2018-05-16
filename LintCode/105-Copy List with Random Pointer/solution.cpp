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
    /**
     * @param head: The head of linked list with a random pointer.
     * @return: A new head of a deep copy of the list.
     */
    RandomListNode* duplicate_list(RandomListNode *head)
    {
        RandomListNode* node = head;
        while(node)
        {
            RandomListNode* dup = new RandomListNode(node->label);
            dup->next = node->next;
            node->next = dup;
            node = dup->next;
        }
        return head;
    }
    
    RandomListNode* set_random_pointers(RandomListNode* head)
    {
        RandomListNode* node = head;
        while(node)
        {
            if(node->random)
                node->next->random = node->random->next;
            node = node->next->next;
        }
        return head;
    }
    
    RandomListNode* separate_deep_copy_list(RandomListNode* head)
    {
        RandomListNode* node = head, *new_node = head->next;
        RandomListNode* new_head = head->next;
        while(new_node->next)
        {
            node->next = new_node->next;
            new_node->next = new_node->next->next;
            node = node->next;
            new_node = new_node->next;
        }
        node->next = NULL;
        return new_head;
    }
    RandomListNode *copyRandomList(RandomListNode *head) {
        // write your code here
        if(!head)
            return NULL;
        head = duplicate_list(head);
        head = set_random_pointers(head);
        head = separate_deep_copy_list(head);
        return head;
    }
};
