/*
 * 题目描述： 给定商品订单数量数组orders=[2, 3, 1],
 * 以及多种生产组合bom1=[2,1,1], bom2=[1,1,0], bom3=[0,1,1],
 * 求最优生产组合
 * 要求：(1)优先使剩余商品种类最少。(2)若剩余商品种类相同，优先使选择生产组合种类数量最少
 * 样例输出：
 * bom2*2,bom3*1
*/
#include <iostream>
#include <vector>
#include <map>
#include <climits>

using namespace std;


void solve(vector<int> &orders, vector<pair<string, vector<int>>> &boms, vector<int> &best,
           vector<int> current, int idx)
{
    int n = orders.size();
    int m = boms.size();
    if(idx == m)
    {
        int cnt = 0, best_cnt = 0, cnt_cate = 0, cnt_best_cate = 0;
        for(int j = 0; j < n; j++)
        {
            int sum = 0, best_sum = 0;
            for(int i = 0; i < m; i++)
            {
                sum += current[i] * boms[i].second[j];
                best_sum += best[i] * boms[i].second[j];
                if(j == 0)
                {
                    if(current[i])
                        cnt_cate++;
                    if(best[i])
                        cnt_best_cate++;
                }
            }
            if(sum != orders[j])
                cnt++;
            if(best_sum != orders[j])
                best_cnt++;
        }
        if(cnt < best_cnt || (cnt == best_cnt && cnt_cate < cnt_best_cate))
            best = current;
        return;
    }
    int limit = INT_MAX;  // Maybe TLE
    for(int j = 0; j < n; j++)
    {
        int remain = orders[j];
        for(int i = 0; i < idx; i++)
            remain -= current[i] * boms[i].second[j];
        if(boms[idx].second[j] == 0)
            continue;
        limit = min(limit, remain / boms[idx].second[j]);
    }
    for(int k = 0; k <= limit; k++)
    {
        vector<int> new_current(current.begin(), current.end());
        new_current[idx] = k;
        solve(orders, boms, best, new_current, idx + 1);
    }
}


void solve(vector<int> &orders, map<string, vector<int>> &_boms)
{
    int m = _boms.size();
    int n = orders.size();
    vector<int> best(m, 0), current(m, 0);
    vector<pair<string, vector<int>>> boms;
    for(auto x: _boms)
        boms.push_back({x.first, x.second});
    solve(orders, boms, best, current, 0);
    bool first = true;
    for(int i = 0; i < n; i++)
        if(best[i])
        {
            if(!first)
                cout<<",";
            cout<<boms[i].first<<"*"<<best[i];
            first = false;
        }
    cout<<endl;
}


int main()
{
    vector<int> orders{2,3,1};
    map<string, vector<int>> boms{
        {"bom1", {2,1,1}},
        {"bom2", {1,1,0}},
        {"bom3", {0,1,1}}};
    solve(orders, boms);
    return 0;
}
