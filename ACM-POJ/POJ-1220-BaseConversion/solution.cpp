// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-30 09:21
// Last modified: 2016-07-30 10:51
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>

const int N=555;

char s[N], d[N];
int t[N], A[N];
int k, i, l;
int a, b;
int CASE;


int main()
{
    scanf("%d", &CASE);
    while(CASE--)
    {
        scanf("%d %d %s", &a, &b, s);
        // Convert every digit of s[i] in base a to base 10
        // And stores in array t reversely
        // SRC s: high(0) .... low(n-1)
        // DST t: low(0)  .... high(n-1)
        for(k=0, i=strlen(s)-1; 0 <= i; i--, k++)
            t[k] = s[i] - (s[i] < 58? 48: s[i] < 97? 55: 61);
        k=strlen(s);
        for(l=0; k;)
        {
            // i start from k to 1, for k = n at first,
            // so t[i-1] += t[i] % b * a will no be difference.
            for(i=k; 1<i--;)
            {
                t[i-1] += t[i]%b*a;
                t[i] /= b;
            }
            // A stores in base b and low(0) ... high(n-1)
            A[l++] = t[0]%b;
            t[0] /= b;
            // Find last available value in t.
            for(;k>0&&!t[k-1];k--);
        }
        // Present every digit of A[i] in base b to its char
        for(d[l]=i=0; i < l; i++)
            d[l-1-i] = A[i] + (A[i] < 10? 48: A[i] < 36? 55: 61);
        printf("%d %s\n%d %s\n\n", a, s, b, d);
    }
    return 0;
}
