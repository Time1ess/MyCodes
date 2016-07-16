// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-16 14:42
// Last modified: 2016-07-16 15:00
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#define N 100003

struct Node
{
    int hash;
    Node *next;
};

Node *links[N] = {0};

char english[N][11], foreign[N][11];

int ElfHash(char *s)
{
    unsigned long h = 0, g;
    while(*s)
    {
        h = (h<<4) + *s++;
        g = h & 0xF0000000L;
        if(g)
        {
            h ^= g>>24;
            h &= ~g;
        }
    }
    return h % N;
}


int main()
{
    char s[25];
    int cnt = 0;
    int hash;
    Node *p;
    while(gets(s) && strcmp(s, "") != 0)
    {
        int i;
        for(i = 0; s[i] != ' '; i++)
            english[cnt][i] = s[i];
        english[cnt][i++] = '\0';
        strcpy(foreign[cnt], s+i);
        hash = ElfHash(foreign[cnt]);
        p = (Node *)malloc(sizeof(Node));
        p->hash = cnt;
        p->next = links[hash];
        links[hash] = p;
        cnt++;
    }
    while(gets(s) && strcmp(s, "") != 0)
    {
        hash = ElfHash(s);
        p = links[hash];
        while(p != NULL)
        {
            if(strcmp(s, foreign[p->hash]) == 0)
                break;
            p = p->next;
        }
        if(p == NULL)
            printf("eh\n");
        else
            printf("%s\n", english[p->hash]);
    }
    return 0;
}
