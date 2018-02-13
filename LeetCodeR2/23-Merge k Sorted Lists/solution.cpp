/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct PointerCompare
{
    bool operator()(const ListNode* a, const ListNode* b)
    {
        return a->val > b->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode new_head(0), *tail;
        priority_queue<ListNode*, vector<ListNode*>, PointerCompare> pq;
        for(auto x: lists)
            if(x)
                pq.push(x);
        while(!pq.empty())
        {
            ListNode *node = pq.top();
            pq.pop();
            if(node->next)
            {
                pq.push(node->next);
                node->next = NULL;
            }
            if(new_head.next)
                tail->next = node;
            else
                new_head.next = node;
            tail = node;
        }
        return new_head.next;
    }
};
