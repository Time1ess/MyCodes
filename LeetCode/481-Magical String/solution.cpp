// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-01-17 15:02
// Last modified: 2017-01-17 15:02
// Filename: solution.cpp
// Description:
class Solution {
public:
    int magicalString(int n) {
        int ones = 1;
        int i=3;
        if(n<=0)
            return 0;
        else if(n<=i)
            return ones;
        int cnt, cur = 2;
        queue<int> q;
        q.push(2);
        while(i<=n)
        {
            cur = cur == 1? 2: 1;
            cnt = q.front();
            q.push(cur);
            if(cnt==2)
                q.push(cur);
            else
                ones++;
            q.pop();
            i++;
        }
        return ones;
    }
};
