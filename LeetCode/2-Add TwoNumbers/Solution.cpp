#define NULL nullptr
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		ListNode *ans,*newnode,*end;
		ans = new ListNode(0);
		end = ans;
		int adding = 0;
		while (l1 != NULL||l2 != NULL||adding)
		{
			int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + adding;
			adding = sum / 10;
			ans->next=new ListNode(sum % 10);
			ans = ans->next;
			l1 = l1 ? l1->next : l1;
			l2 = l2 ? l2->next : l2;
		}
		return end->next;
	}
};