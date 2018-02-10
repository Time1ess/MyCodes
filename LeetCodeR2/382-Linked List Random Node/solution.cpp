/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
    ListNode* head;
public:
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) {
        this->head = head;
    }
    
    /** Returns a random node's value. */
    int getRandom() {
        int k = 1;
        ListNode *tmp = head;
        vector<int> pool;
        for(int i = 0; i < k; i++)
        {
            pool.push_back(tmp->val);
            tmp = tmp->next;
        }
        int i = 1;
        while(tmp)
        {
            int p = rand() % (k + i);
            i++;
            if(p < k)
                pool[p] = tmp->val;
            tmp = tmp->next;
        }
        return pool[0];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(head);
 * int param_1 = obj.getRandom();
 */
