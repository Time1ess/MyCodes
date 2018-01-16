/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    void construct(vector<int> &ans, ListNode* head)
    {
        if(!head) return;
        construct(ans, head->next);
        ans.push_back(head->val);
    }
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> ans;
        construct(ans, head);
        return ans;
    }
};
