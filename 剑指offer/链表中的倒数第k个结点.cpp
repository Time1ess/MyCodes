/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        if(!pListHead || k == 0)
            return NULL;
    	ListNode* k_ahead = pListHead;
        int cnt = 1;
        while(cnt < k && k_ahead->next != NULL)
        {
            k_ahead = k_ahead->next;
            cnt++;
        }
        if(cnt < k)
            return NULL;
        ListNode* root=pListHead;
        while(k_ahead->next)
        {
            root = root->next;
            k_ahead = k_ahead->next;
        }
        return root;
    }
};
