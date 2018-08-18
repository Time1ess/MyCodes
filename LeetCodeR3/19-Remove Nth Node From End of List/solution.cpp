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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode* tail = head;
        ListNode* tar = head;
        for (int i = 0; i < n && tail != nullptr; i++) {
            tail = tail->next;
        }
        if (tail == nullptr) {
            ListNode* tmp = head->next;
            delete head;
            return tmp;
        }
        while (tail->next != nullptr) {
            tar = tar->next;
            tail = tail->next;
        }
        ListNode* tmp = tar->next;
        tar->next = tmp->next;
        delete tmp;
        return head;
    }
};
