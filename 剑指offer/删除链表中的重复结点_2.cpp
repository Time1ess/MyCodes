#include <iostream>
#include <vector>

using namespace std;


struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x)
    {
        val = x;
        next = NULL;
    }
};


ListNode* build_list(vector<int> &vals, int idx)
{
    int size = vals.size();
    if(idx == size)
        return NULL;
    ListNode* node = new ListNode(vals[idx]);
    node->next = build_list(vals, idx+1);
    return node;
}


void RemoveDuplicates(ListNode **head)
{
    if(!head || !(*head))
        return;
    ListNode *pre, *node;
    pre = NULL;
    node = *head;
    while(node)
    {
        ListNode *next = node->next;
        bool should_delete = false;
        if(next && next->val == node->val)
            should_delete = true;
        if(!should_delete)
        {
            pre = node;
            node = node->next;
        }
        else
        {
            int val = node->val;
            ListNode *tmp=node;
            while(tmp && tmp->val == val)
            {
                next = tmp->next;
                delete tmp;
                tmp = NULL;
                
                tmp = next;
            }
            if(!pre)
                *head = next;
            else
                pre->next = next;
            node = next;
        }
    }
}


int main()
{
    vector<int> vals{1,1,2,3,3,4,5,5};
    ListNode *head = build_list(vals, 0);
    ListNode *node = head;
    while(node)
    {
        cout<<node->val<<endl;
        node = node->next;
    }
    RemoveDuplicates(&head);
    node = head;
    cout<<"After"<<endl;
    while(node)
    {
        cout<<node->val<<endl;
        node = node->next;
    }
    return 0;
}
