#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
char mp[10][10];
int dp[4][4];
int getnum(int flag){
    int res=0;
    while(flag){
        res+=flag%2;
        flag/=2;
    }
    return res;
}
int Vis[4],Max=0;
void dfs(vector<vector<int> > &vec,int po,int n){
    if(po==n){
        int sum=0;
        for(int i=0;i<4;i++){
            if(Vis[i]){
                sum++;
            }
        }
        Max=max(sum,Max);
        return;
    }
    int size=vec[po].size();
    for(int i=0;i<size;i++){
        Vis[vec[po][i]]++;
        dfs(vec,po+1,n);
        Vis[vec[po][i]]--;
    }
}
bool ck(int n){

    for(int i=0;i<n;i++){
        int sum=0;
        for(int j=0;j<n;j++){
            sum+=dp[i][j];
        }
        if(sum==n)
            continue;
        if(sum==0)
            return false;
        vector<vector<int> > vec;
        for(int j=0;j<n;j++){
            if(dp[i][j]){
                vector<int> tmp;
                for(int k=0;k<n;k++){
                    if(k==i)
                        continue;
                    if(dp[k][j])
                        tmp.push_back(k);
                }
                vec.push_back(tmp);
            }
        }
        Max=0;
        dfs(vec,0,vec.size());
        if(Max>=sum)
            return false;

    }
    return true;
}
int main()
{
    int ncase,T=0;
    scanf("%d",&ncase);
    while(ncase--){
        printf("Case #%d: ",++T);
        int n;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%s",mp[i]);
        vector<int> po;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                dp[i][j]=mp[i][j]-'0';
                if(dp[i][j]==0)
                    po.push_back(i*n+j);
            }
        int size=po.size();
        int limit=1<<size;
        int ans=size;
        for(int flag=0;flag<limit;flag++){
            for(int j=0;j<size;j++){
                if((flag>>j)&1){
                    int x=po[j]/n;
                    int y=po[j]%n;
                    dp[x][y]=1;
                }
            }
            if(ck(n)){
                ans=min(ans,getnum(flag));
            }
            for(int j=0;j<size;j++){
                if((flag>>j)&1){
                    int x=po[j]/n;
                    int y=po[j]%n;
                    dp[x][y]=0;
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
