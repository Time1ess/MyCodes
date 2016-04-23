#include <iostream>
#include <cstring>
#include <cmath>

#define max(a,b) a>b?a:b
using namespace std;

int p[1005], h[1005], c[1005];
int dp[1005];
int n, m ;

void DP()
{
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= c[i]; j++)
            for(int k = n; k >= p[i] ; k --)
                dp[k] = max(dp[k-p[i]]+h[i],dp[k]);
}

int main()
{
    int CASE;
    scanf("%d", &CASE);
    while(CASE--)
    {
        scanf("%d%d", &n, &m);
        memset(dp, 0 , sizeof(dp));
        for(int i = 1; i <= m; i++)
            scanf("%d%d%d", &p[i], &h[i], &c[i]);
        DP();
        printf("%d\n",dp[n]);
    }
    return 0;
}
    
