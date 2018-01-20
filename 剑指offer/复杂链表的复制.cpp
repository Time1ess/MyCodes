/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if(!pHead)
            return NULL;
        RandomListNode *node = pHead;
        while(node != NULL)  // Duplicate nodes
        {
            RandomListNode *new_node = new RandomListNode(node->label);
            new_node->next = node->next;
            node->next = new_node;
            node = new_node->next;
        }
        node = pHead;
        while(node != NULL)  // Set random pointer
        {
            if(node->random)
            	node->next->random = node->random->next;
            node = node->next->next;
        }
        node = pHead;
        RandomListNode *new_head, *new_node;
        new_head = new_node = node->next;
        node->next = new_node->next;
        node = node->next;
        while(node != NULL && new_node != NULL)  // Separate duplicates and origins
        {
            new_node->next = node->next;
            new_node = new_node->next;
            node->next = new_node->next;
            node = node->next;
        }
        return new_head;
    }
};
