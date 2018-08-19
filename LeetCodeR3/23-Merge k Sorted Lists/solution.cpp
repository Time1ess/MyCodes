/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct Cmp {
    bool operator()(const ListNode* l1, const ListNode* l2) {
        return l1->val > l2->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Cmp> pq;
        for (auto l: lists) {
            if (l == nullptr) {
                continue;
            }
            pq.push(l);
        }
        ListNode new_head(0);
        ListNode* tail = &new_head;
        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            ListNode* next = top->next;
            top->next = nullptr;
            tail->next = top;
            tail = tail->next;
            if (next != nullptr) {
                pq.push(next);
            }
        }
        return new_head.next;
    }
};
