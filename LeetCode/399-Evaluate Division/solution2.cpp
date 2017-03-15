// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-15 17:55
// Last modified: 2017-03-15 17:55
// Filename: solution2.cpp
// Description:
class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        map<string, map<string, bool>> rels;
        map<pair<string, string>, double> vals;
        vector<double> ans;
        int size = equations.size();
        string f, s;
        for(int i = 0; i < size; i++)
        {
            f = equations[i].first;
            s = equations[i].second;
            rels[f][s] = true;
            rels[s][f] = true;
            vals[equations[i]] = values[i];
            vals[make_pair(s, f)] = 1 / values[i];
        }
        for(auto x: queries)
        {
            auto search = rels.find(x.first);
            map<string, bool> lookups;
            if(search == rels.end())
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
            ans.push_back(get_query(f, s, rels, vals, lookups));
        }
        return ans;
    }
    double get_query(string &a, string &b, map<string, map<string, bool>> &rels, 
                     map<pair<string, string>, double> &vals, map<string, bool> &lookups)
    {
        if(lookups[a] == true)
            return -1;
        lookups[a] = true;
        if(rels[a].find(b) != rels[a].end())
            return vals[make_pair(a, b)];
        double res;
        string c;
        for(auto t: rels[a])
        {
            c = t.first;
            res = get_query(c, b, rels, vals, lookups);
            if(fabs(res + 1) > 1e-5)
                return vals[make_pair(a, c)] * res;
        }
        return -1;
    }
};
