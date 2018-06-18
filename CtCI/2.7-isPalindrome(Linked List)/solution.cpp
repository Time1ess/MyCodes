/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};*/
class Palindrome {
public:
    bool isPalindrome(ListNode* pHead) {
        // write code here
        int n = 0;
        ListNode* node = pHead;
        while(node) {
            n++;
            node = node->next;
        }
        node = pHead;
        stack<int> s;
        for(int i = 0; i < n / 2; i++) {
            s.push(node->val);
            node = node->next;
        }
        if((n & 1) != 0)
            node = node->next;
        while(node) {
            if(node->val != s.top())
                return false;
            s.pop();
            node = node->next;
        }
        return true;
    }
};
