/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if(!pHead || pHead->next == NULL)
            return pHead;
        ListNode *pre, *node;
        pre = NULL;
        ListNode new_head(0);
        node = pHead;
        while(node)
        {
            ListNode *next = node->next;
            bool need_delete = false;
            if(next && next->val == node->val)
                need_delete = true;
            if(!need_delete)
            {
                pre = node;
                if(new_head.next == NULL)
                    new_head.next = pre;
                node = node->next;
            }
            else
            {
                int val = node->val;
                ListNode *to_be_delete = node;
                while(to_be_delete && to_be_delete->val == val)
                {
                    next = to_be_delete->next;
                    delete to_be_delete;
                    to_be_delete = NULL;
                    
                    to_be_delete = next;
                }
                if(pre)
                    pre->next = next;
                else
                    new_head.next = next;
                node = next;
            }
        }
        return new_head.next;
    }
};
