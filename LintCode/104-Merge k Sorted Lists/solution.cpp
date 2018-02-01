#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class ListNode {
public:
    int val;
    ListNode *next;
    ListNode(int val) {
        this->val = val;
        this->next = NULL;
    }
};


class Solution {
public:
    /**
     * @param lists: a list of ListNode
     * @return: The head of one sorted list.
     */
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // write your code here
        auto cmp = [](ListNode *a, ListNode *b)
        {
            return a->val > b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
        int size = lists.size();
        for(int i = 0; i < size; i++)
            if(lists[i] != NULL)
                pq.push(lists[i]);
        ListNode *head, *node;
        head = NULL;
        node = NULL;
        while(!pq.empty())
        {
            ListNode *tmp = pq.top();
            pq.pop();
            if(tmp->next)
                pq.push(tmp->next);
            tmp->next = NULL;
            if(!head)
                head = tmp;
            else
                node->next = tmp;
            node = tmp;
        }
        return head;
    }
};

ListNode* build_list(vector<int> s, int idx)
{
    int size = s.size();
    if(idx >= size)
        return NULL;
    ListNode *head = new ListNode(s[idx]);
    head->next = build_list(s, idx+1);
    return head;
}

int main()
{
    vector<ListNode*> s = {
        build_list({2,4}, 0),
        NULL,
        build_list({-1}, 0)};
    for(auto x: s)
    {
        auto t = x;
        while(t)
        {
            t = t->next;
        }
        cout<<endl;
    }
    Solution sol;
    ListNode *head = sol.mergeKLists(s);
    ListNode *tmp = head;
    while(tmp)
    {
        cout<<tmp->val<<endl;
        tmp = tmp->next;
    }
    return 0;
}
