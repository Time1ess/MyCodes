// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-26 10:09
// Last modified: 2017-07-26 10:09
// Filename: solution.cpp
// Description:
class Solution {
public:
    string countAndSay(int n) {
        queue<int> q[2];
        q[0].push(1);
        int now = 0, last = 1;
        int num = 0, cnt = 0;
        for(int i = 1; i < n; i++)
        {
            swap(now, last);
            while(!q[last].empty())
            {
                cnt = 0;
                num = q[last].front();
                q[last].pop();
                cnt++;
                while(!q[last].empty() && q[last].front() == num)
                {
                    q[last].pop();
                    cnt++;
                }
                q[now].push(cnt);
                q[now].push(num);
            }
        }
        stringstream result;
        while(!q[now].empty())
        {
            result<<q[now].front();
            q[now].pop();
        }
        return result.str();
    }
};
