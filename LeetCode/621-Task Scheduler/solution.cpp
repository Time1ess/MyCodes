// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-22 17:15
// Last modified: 2017-06-22 17:15
// Filename: solution.cpp
// Description:
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int tasks_cnt[26] = {0};
        for(auto x: tasks)
            tasks_cnt[x-'A']++;
        priority_queue<int> pq;
        for(int i = 0; i < 26; i++)
            if(tasks_cnt[i] != 0)
                pq.push(tasks_cnt[i]);
        int global_time = 0;
        while(!pq.empty())
        {
            int t = 0;
            vector<int> tmp;
            for(int i = 0; i < n + 1; i++)
            {
                if(!pq.empty())
                {
                    tmp.push_back(pq.top());
                    pq.pop();
                    t++;
                }
            }
            for(auto x: tmp)
                if(--x)
                    pq.push(x);
            global_time += !pq.empty() ? n+1 : t;
        }
        return global_time;
    }
};
