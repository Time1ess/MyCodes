// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-15 18:08
// Last modified: 2017-03-15 18:08
// Filename: solution3.cpp
// Description:
class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string, vector<pair<string, double>>> vals;
        vector<double> ans;
        int size = equations.size();
        string f, s;
        for(int i = 0; i < size; i++)
        {
            f = equations[i].first;
            s = equations[i].second;
            vals[f].push_back(make_pair(s, values[i]));
            vals[s].push_back(make_pair(f, 1 / values[i]));
        }
        for(auto x: queries)
        {
            auto search = vals.find(x.first);
            unordered_map<string, bool> lookups;
            if(search == vals.end())
            {
                ans.push_back(-1);
                continue;
            }
            else if(x.first == x.second)
            {
                ans.push_back(1);
                continue;
            }
            f = x.first;
            s = x.second;
            ans.push_back(get_query(f, s, vals, lookups));
        }
        return ans;
    }
    double get_query(string &a, string &b, unordered_map<string ,vector<pair<string, double>>> &vals, unordered_map<string, bool> &lookups)
    {
        if(lookups[a] == true)
            return -1;
        lookups[a] = true;
        double res;
        string c;
        for(auto t: vals[a])
        {
            c = t.first;
            if(c == b)
                return t.second;
            res = get_query(c, b, vals, lookups);
            if(fabs(res + 1) > 1e-5)
                return t.second * res;
        }
        return -1;
    }
};
