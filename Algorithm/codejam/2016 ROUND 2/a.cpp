#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, R, P, S;

string dfs(string cur) {
    int len = cur.length();
    if(len == 1) return cur;
    if(len == 0) return "";
    string L = cur.substr(0, len / 2), R = cur.substr(len / 2, len / 2);
    L = dfs(L), R = dfs(R);
    return min(L + R, R + L);
}
string get(int n, int R, int P, int S, int winner) {
    string ret = "";
    if(winner == 0 && R) ret = "R", R--;
    else if(winner == 1 && P) ret = "P", P--;
    else if(winner == 2 && S) ret = "S", S--;
    for(int i = 0; i < n; ++i) {
        string cur = "";
        for(int j = 0; j < ret.length(); ++j) {
            if(ret[j] == 'R') {
                cur += "RS";
                S--;
            }
            else if(ret[j] == 'P') {
                cur += "PR";
                R--;
            }
            else {
                cur += "PS";
                P--;
            }
        }
        if(P < 0 || R < 0 || S < 0) return "";
        ret = cur;
    }
    return dfs(ret);
}
int main() {
    int _, cas = 1;
    for(scanf("%d", &_); _--; ) {
        printf("Case #%d: ", cas++);
        scanf("%d %d %d %d", &n, &R, &P, &S);
        string ans = "";
        for(int i = 0; i < 3; ++i) {
            string ret = get(n, R, P, S, i);
            if(ret == "") continue;
            if(ans == "") ans = ret;
            else ans = min(ans, ret);
        }
        if(ans == "") puts("IMPOSSIBLE");
        else cout << ans << endl;
    }
    return 0;
}
