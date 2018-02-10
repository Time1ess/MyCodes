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
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        vector<ListNode*> ans;
        if(!root)
        {
            for(int i = 0; i < k; i++)
                ans.push_back(NULL);
            return ans;
        }
        int cnt = 0;
        ListNode *tmp = root;
        while(tmp)
        {
            cnt++;
            tmp = tmp->next;
        }
        int div = cnt / k, mod = cnt % k;
        if(div == 0)
        {
            while(root && k--)
            {
                tmp = root->next;
                root->next = NULL;
                ans.push_back(root);
                root = tmp;
            }
            while(k--)
                ans.push_back(NULL);
        }
        else
        {
            while(k--)
            {
                ListNode *head;
                head = tmp = root;
                for(int i = 1; i < div; i++)
                    tmp = tmp->next;
                if(mod-- > 0)
                    tmp = tmp->next;
                root = tmp->next;
                tmp->next = NULL;
                ans.push_back(head);
            }
        }
        return ans;
    }
};
