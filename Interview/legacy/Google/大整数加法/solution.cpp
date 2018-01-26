#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;


void big_add(char **a, int t, char **b, int m)
{
    int i = t - 1, j = m - 1, c = 0;
    int tmp;
    while(i >= 0 || j >= 0)
    {
        tmp = (j >= 0 ? (*b)[j] - '0': 0) + (*a)[i] - '0' + c;
        c = 0;
        if(tmp >= 10)
        {
            c = 1;
            tmp %= 10;
        }
        if(j >= 0)
            j--;
        (*a)[i--] = tmp + '0';
    }
    if(c == 1)
        (*a)[0] = '1';
    if((*a)[0] != '1')
    {
        memmove(*a, (*a)+1, t - 1);
        (*a)[t-1] = '\0';
    }
}


int main()
{
    int n = 28;
    int m = 29;
    int t = 1 + max(n, m);
    char *a = (char*)malloc(sizeof(char) * t);
    char *b = (char*)malloc(sizeof(char) * m);
    for(int i = 0; i < t - n; i++)
        a[i] = '0';
    for(int i = t - n; i < t; i++)
        a[i] = '0' + (i + 1) % 10;
    for(int j = 0; j < m; j++)
        b[j] = '0' + (j + 1) % 10;
    for(int i = 0; i < t; i++)
        cout<<a[i];
    cout<<endl;
    for(int j = 0; j < m; j++)
        cout<<b[j];
    cout<<endl;
    big_add(&a, t, &b, m);
    for(int i = 0; i < t; i++)
        cout<<a[i];
    free(a);
    free(b);
    a = NULL;
    b = NULL;
    return 0;
}
