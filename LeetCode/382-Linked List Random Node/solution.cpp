// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-09-17 14:14
// Last modified: 2016-09-17 14:14
// Filename: solution.cpp
// Description:
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
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) {
        this->node_num = 0;
        this->head = head;
    }
    
    /** Returns a random node's value. */
    int getRandom() {
        ListNode* tmp;
        if(this->node_num==0)
        {
            tmp=this->head;
            do
            {
                this->node_num ++;
                tmp = tmp->next;
            }while(tmp);
        }
        int cnt = rand()%this->node_num;
        tmp = this->head;
        while(cnt--)
            tmp = tmp->next;
        return tmp->val;
        
    }
private:
    int node_num;
    ListNode* head;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(head);
 * int param_1 = obj.getRandom();
 */
