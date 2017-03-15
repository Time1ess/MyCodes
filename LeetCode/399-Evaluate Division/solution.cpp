// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-15 17:14
// Last modified: 2017-03-15 17:14
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        map<pair<string, string>, double> valm;
        queue<pair<string, string>> q;
        string fn, fd, sn, sd;
        pair<string, string> z, rz;
        double vx, vy;
        int size = equations.size();
        for(int i = 0; i < size; i++)
        {
            valm[equations[i]] = values[i];
            fn = equations[i].first;
            fd = equations[i].second;
            valm[make_pair(fd, fn)] = 1 / values[i];
            valm[make_pair(fd, fd)] = valm[make_pair(fn, fn)] = 1;
            q.push(equations[i]);
        }
        while(!q.empty())
        {
            auto x = q.front();
            q.pop();
            fn = x.first;
            fd = x.second;
            vx = valm[x];
            for(auto y: valm)
            {
                sn = y.first.first;
                sd = y.first.second;
                vy = y.second;
                if(fd == sn)
                {
                    z = make_pair(fn, sd);
                    if(valm.find(z) != valm.end())
                        continue;
                    rz = make_pair(sd, fn);
                    valm[z] = vx * vy;
                    valm[rz] = 1 / (vx * vy);
                }
                else if(fd == sd)
                {
                    z = make_pair(fn, sn);
                    if(valm.find(z) != valm.end())
                        continue;
                    rz = make_pair(sn, fn);
                    valm[z] = vx / vy;
                    valm[rz] = vy / vx;
                }
                else if(fn == sn)
                {
                    z = make_pair(sd, fd);
                    if(valm.find(z) != valm.end())
                        continue;
                    rz = make_pair(fd, sd);
                    valm[z] = vx / vy;
                    valm[rz] = vy / vx;
                }
            }
        }
        vector<double> ans;
        for(auto x: queries)
        {
            auto search = valm.find(x);
            if(search != valm.end())
                ans.push_back(search->second);
            else
                ans.push_back(-1);
        }
        return ans;
    }
};
