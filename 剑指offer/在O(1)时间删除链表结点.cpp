#include <iostream>
using namespace std;


struct ListNode
{
    int val;
    ListNode *next;
};


void print_list(ListNode* head, bool first=false)
{
    if(!head)
        return;
    if(!first)
        cout<<"->";
    cout<<head->val;
    print_list(head->next);
    if(first)
        cout<<endl;
}


void DeleteNode(ListNode** head, ListNode* deleted)
{
    if(!head || !deleted)
        return;
    
    if(deleted->next)
    {
        ListNode* tmp = deleted->next;
        deleted->val = tmp->val;
        deleted->next = tmp->next;

        delete tmp;
        tmp = NULL;
    }
    else if(*head == deleted)
    {
        delete deleted;
        deleted = NULL;
        *head = NULL;
    }
    else
    {
        ListNode* tmp = *head;
        while(tmp->next != deleted)
            tmp = tmp->next;
        tmp->next = NULL;
        delete deleted;
        deleted = NULL;
    }
}


ListNode* build_list(int arr[], int n)
{
    if(n == 0)
        return NULL;
    else
    {
        ListNode* head = new ListNode();
        head->val = arr[n-1];
        head->next = build_list(arr, n-1);
        return head;
    }
}

void destroy_list(ListNode** head)
{
    while(*head)
        DeleteNode(head, *head);
}


int main()
{
    int arr[] = {1,2,3};
    ListNode* head;

    head = build_list(arr, 3);
    DeleteNode(&head, head->next->next);
    print_list(head, true);
    destroy_list(&head);

    head = build_list(arr, 3);
    DeleteNode(&head, head->next);
    print_list(head, true);
    destroy_list(&head);

    head = build_list(arr, 3);
    DeleteNode(&head, head);
    print_list(head, true);
    destroy_list(&head);

    return 0;
}
