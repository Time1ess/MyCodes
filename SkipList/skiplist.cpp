// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-14 10:10
// Last modified: 2016-07-15 09:48
// Filename: skiplist.cpp
// Description: TODO: remains bug
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

#define MAXlevel 10


struct Node
{
    int key;
    Node *next[MAXlevel];
};

Node *Init(int &level)
{
    Node *head = (Node *)malloc(sizeof(Node));
    for(int i = 0; i < MAXlevel; i++)
        head->next[i] = 0;
    head->key = 0;
    level = 0;
    return head;
}

int GetLevel(int &level)
{
    int t, i, j;
    t = rand();
    for(i = 0, j = 2; i < MAXlevel; i++, j<<=1)
        if(t > RAND_MAX/j)
            break;
    if(i > level)
        level = i;
    return i;
}

void Insert(Node *head, int key, int &level)
{
    Node *p, *nexts[MAXlevel];
    int Nlevel;
    p = head;
    Nlevel = GetLevel(level);
    for(int i = level; i >= 0; i--)
    {
        while((p->next[i] != 0)&&(p->next[i]->key < key))
            p = p->next[i];
        nexts[i] = p;
    }
    p = (Node *)malloc(sizeof(Node));
    p->key = key;
    for(int i = 0; i < MAXlevel; i++)
        p->next[i] = 0;
    for(int i = Nlevel; i >= 0; i--)
    {
        p->next[i] = nexts[i]->next[i];
        nexts[i]->next[i] = p;
    }
}

void Print(Node *head, int level)
{
    printf("\n");
    for(int i = level; i >= 0; i--)
    {
        Node *p, *q;
        p = q = head;
        printf("Level %d: ", i);
        while(p != 0)
        {
            while(i != 0 &&q->key != p->key && q->next[0] != 0)
            {
                printf("     ");
                q = q->next[0];
            }
            printf("  %3d", p->key);
            p = p->next[i];
            if(q->next[0])
                q = q->next[0];
        }
        printf("\n");
    }
}

Node *Search(Node *head, int key, int level)
{
    Node *p = head;
    for(int i = level; i >= 0; i--)
        while(p->next[i] != 0 && p->next[i]->key < key)
            p = p->next[i];
    p = p->next[0];
    if(p == 0)
        return 0;
    else if(p->key == key)
        return p;
    else
        return 0;
}

int Delete(Node *head, int key, int &level)
{
    Node *t = Search(head, key, level);
    if(t != 0)
    {
        Node *p, *q;
        int i = level;
        while(i >= 0)
        {
            p = q = head;
            while(p != t && p != 0)
            {
                q = p;
                p = p->next[i];
            }
            if(p != 0)
            {
                if(i == level && q == head && p->next[i] == 0)
                    level--;
                else
                    q->next[i] = p->next[i];
            }
            i--;
        }
        free(t);
        return 1;
    }
    else
        return 0;
}

int main()
{
    Node *head;
    int level;
    head = Init(level);
    srand((unsigned int)time(0));
    char cmd[3];
    int key;
    while(scanf("%s", cmd)&& cmd[0] != 'e')
    {
        if(cmd[0] == 'i')
        {
            scanf("%d", &key);
            printf("--%c %d\n", cmd[0], key);
            Insert(head, key, level);
        }
        else if(cmd[0] == 'p')
        {
            printf("--%c\n", cmd[0]);
            Print(head, level);
        }
        else if(cmd[0] == 's')
        {
            scanf("%d", &key);
            printf("--%c %d\n", cmd[0], key);
            Node *p = Search(head, key, level);
            if(p == 0)
                printf("Node not found: %d\n", key);
            else
                printf("Node found: %d\n", p->key);
        }
        else if(cmd[0] == 'd')
        {
            scanf("%d", &key);
            printf("--%c %d\n", cmd[0], key);
            int status = Delete(head, key, level);
            if(status == 1)
                printf("Delete succeeded: %d\n", key);
            else
                printf("Delete failed: %d\n", key);
        }
        else
        {
            printf("unknown command.\n");
        }
    }
    return 0;
}
