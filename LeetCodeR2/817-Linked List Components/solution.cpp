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
    int numComponents(ListNode* head, vector<int>& G) {
        if(!head)
            return 0;
        unordered_set<int> g;
        for(auto x: G)
            g.insert(x);
        int ans = 0;
        bool current = false;
        while(head)
        {
            if(g.find(head->val) != g.end())
            {
                if(!current)
                {
                    ans++;
                    current = true;
                }
            }
            else
                current = false;
            head = head->next;
        }
        return ans;
    }
};
