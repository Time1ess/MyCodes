// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-04-16 10:20
// Last modified: 2016-04-16 10:22
// Filename: solution2.cpp
// Description:
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;


const int N = 1010;
const int inf = ~0U >> 1;
const int mod = 1e9 + 7;

int n;
int bff[N], idx[N];
vector<int> e[N];

int get_circle(int start) {
    memset(idx, -1, sizeof(idx));
    int cnt = 0;
    while(idx[start] == -1) {   
        idx[start] = ++cnt;
        start = bff[start];
    }
    if(idx[start] == 1) return cnt;
    return 0;
}

int dfs(int x, int father) {
    int dep = 0;
    for(int i = 0; i < e[x].size(); ++i) {
        int y = e[x][i];
        if(y == father) continue;
        dep = max(dep, dfs(y, x));
    }
    return dep + 1;
}
int main() {
    int _, _cas = 0;
    for(scanf("%d", &_); _--; ) {
        printf("Case #%d: ", ++_cas);
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) e[i].clear();
        for(int i = 1; i <= n; ++i) {
            scanf("%d", bff + i);
            e[bff[i]].push_back(i);
        }
        int ans = 0;
        for(int i = 1; i <= n; ++i) {
            ans = max(ans, get_circle(i));
        }
        
        int len = 0;
        for(int i = 1; i <= n; ++i) {
            if(bff[bff[i]] == i && i <= bff[i]) {
                len += dfs(i, bff[i]) + dfs(bff[i], i);
            }
        }
        cout << max(ans, len) << endl;
    }
    return 0;
}
