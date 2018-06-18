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
        if(k == 0)
            return NULL;
        ListNode* node = pListHead;
        int j = 0;
        while(j < k && node) {
            j++;
            node = node->next;
        }
        if(j < k)
            return NULL;
        ListNode* ans = pListHead;
        while(node) {
            node = node->next;
            ans = ans->next;
        }
        return ans;
    }
};
