// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-30 08:58
// Last modified: 2017-09-30 08:58
// Filename: solution.cpp
// Description:
/*
// Employee info
class Employee {
public:
    // It's the unique ID of each node.
    // unique id of this employee
    int id;
    // the importance value of this employee
    int importance;
    // the id of direct subordinates
    vector<int> subordinates;
};
*/
class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        unordered_map<int, Employee*> id_sids;
        queue<int> ord_ids;
        set<int> ids;
        for(auto x: employees)
            id_sids[x->id] = x;
        ids.insert(id);
        ord_ids.push(id);
        while(!ord_ids.empty())
        {
            auto k = ord_ids.front();
            ord_ids.pop();
            for(auto y: id_sids[k]->subordinates)
            {
                ids.insert(y);
                ord_ids.push(y);
            }
        }
        int ans = 0;
        for(auto x: ids)
            ans += id_sids[x]->importance;
        return ans;
    }
};
