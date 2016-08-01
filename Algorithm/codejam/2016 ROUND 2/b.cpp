#include <iostream>
#include <cmath>
#include <cstring>
#include <queue>
#include <vector>
#include <cstdio>
#include <map>
#include <stack>
#include <set>
#include <algorithm>
#define ll long long
using namespace std;
const int Maxn = 210 , Maxm = 11, Mo = 1e9 + 7;
const int oo = 1ll << 30;
#define PB push_back

int T, cs = 1;
int n, d, m, nq;
double f[Maxn][Maxn * 2], P[Maxn], w[Maxn], ans;
double aP[Maxn];
void dfs(int pos, int ch){
    if (ch == m + 1){
        memset(f,0,sizeof(f));
        f[0][m + 1] = 1;
        for (int i = 1;i <= m; i++){
                for (int k = -i; k <= i; k++){
                    int zt = k + m + 1;
                    f[i][zt] = f[i-1][zt + 1] * (1 - P[i]) + f[i-1][zt - 1] * P[i];                    
                }
        }
        if (f[m][m+1] >= ans){
            ans = f[m][m+1];
            for (int i=1;i<=m;i++) aP[i] = P[i];
        }
        ans = max(ans, f[m][m + 1]);
        return;
    }
    if (pos > n) return;
    if (m - ch > n - pos) return;
    P[ch] = w[pos];
    dfs(pos + 1, ch + 1);
    dfs(pos + 1, ch);
}
int main(){
    cin >> T;
    for(int cs = 1; cs <= T; cs++){
        printf("Case #%d: ",cs); 
        // puts("");
        cin >> n >> m;
        for (int i = 1;i <= n; i++) cin >> w[i];
        sort(w + 1,w + n + 1);
        ans = -1;
        // dfs(1, 1);
        
        
        for (int pos = 0; pos <= m; pos ++){
            for (int i = 1; i <= pos; i++) P[i] = w[i];
            for (int i = pos + 1; i <= m; i++) P[i] = w[n - i + pos + 1];
            memset(f,0,sizeof(f));
            f[0][m + 1] = 1;
            for (int i = 1;i <= m; i++){
                    for (int k = -m; k <= m; k++){
                        int zt = k + m + 1;
                        f[i][zt] = f[i-1][zt + 1] * (1 - P[i]) + f[i-1][zt - 1] * P[i];                    
                    }
            }    
            ans = max(ans , f[m][m + 1]);
        }        
        // for (int i=1;i<=m;i++) cout << P[i] <<" "; cout << endl;
        // for (int i=1;i<=m;i++) cout << aP[i] <<" "; cout << endl;
        printf("%.10f\n", ans);
        // cout << ans << endl;
    }
}