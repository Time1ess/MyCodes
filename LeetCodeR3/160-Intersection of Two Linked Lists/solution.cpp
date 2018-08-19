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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        int m = 1, n = 1;
        ListNode* la = headA;
        while (la->next) {
            m++;
            la = la->next;
        }
        ListNode* lb = headB;
        while (lb->next) {
            n++;
            lb = lb->next;
        }
        if (la != lb) {
            return nullptr;
        }
        la = headA;
        lb = headB;
        if (m < n) {
            for (int i = m; i < n; i++) {
                lb = lb->next;
            }
        } else {
            for (int i = n; i < m; i++) {
                la = la->next;
            }
        }
        while (true) {
            if (la == lb) {
                return la;
            }
            la = la->next;
            lb = lb->next;
        }
        return nullptr;
    }
};
