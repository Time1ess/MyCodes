// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-07 09:09
// Last modified: 2017-07-07 09:09
// Filename: solution.cpp
// Description:
bool cmp(const pair<string, int> &a, const pair<string, int> &b)
{
    return a.first < b.first;
}
class LogSystem {
private:
    vector<pair<string, int>> vp;
public:
    LogSystem() {
        
    }
    
    void put(int id, string timestamp) {
        pair<string, int> p = make_pair(timestamp, id);
        vp.insert(upper_bound(vp.begin(), vp.end(), p, cmp), p); // insert before the first greater value
    }
    
    vector<int> retrieve(string s, string e, string gra) {
        string start, end;
        vector<int> ans;
        if(gra == "Year")
        {
            start = s.substr(0, 5)+"00:00:00:00:00";
            end = e.substr(0, 5)+"12:31:23:59:59";
        }
        else if(gra == "Month")
        {
            start = s.substr(0, 8)+"00:00:00:00";
            end = e.substr(0, 8)+"31:23:59:59";
        }
        else if(gra == "Day")
        {
            start = s.substr(0, 11)+"00:00:00";
            end = e.substr(0, 11)+"23:59:59";
        }
        else if(gra == "Hour")
        {
            start = s.substr(0, 14)+"00:00";
            end = e.substr(0, 14)+"59:59";
        }
        else if(gra == "Minute")
        {
            start = s.substr(0, 17)+"00";
            end = e.substr(0, 17)+"59";
        }
        else
        {
            start = s;
            end = e;
        }
        auto iter_start = lower_bound(vp.begin(), vp.end(), make_pair(start, -1), cmp); // first not less than s
        auto iter_end = upper_bound(vp.begin(), vp.end(), make_pair(end, -1), cmp); // first greater than e
        for(auto x = iter_start; x != iter_end; x++)
            ans.push_back(x->second);
        return ans;
    }
};

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem obj = new LogSystem();
 * obj.put(id,timestamp);
 * vector<int> param_2 = obj.retrieve(s,e,gra);
 */
