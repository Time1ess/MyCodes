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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode *a, ListNode *b)
        {
            return a->val > b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
        int size = lists.size();
        for(int i = 0; i < size; i++)
            if(lists[i] != NULL)
                pq.push(lists[i]);
        ListNode *head, *node;
        head = NULL;
        node = NULL;
        while(!pq.empty())
        {
            ListNode *tmp = pq.top();
            pq.pop();
            if(tmp->next)
                pq.push(tmp->next);
            tmp->next = NULL;
            if(!head)
                head = tmp;
            else
                node->next = tmp;
            node = tmp;
        }
        return head;
    }
};
