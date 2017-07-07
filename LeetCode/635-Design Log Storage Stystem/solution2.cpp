// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-07 09:17
// Last modified: 2017-07-07 09:17
// Filename: solution2.cpp
// Description:
class LogSystem {
private:
    vector<pair<string, int>> vp;
    unordered_map<string, int> dic={{"Second",0},{"Minute",1},{"Hour",2},{"Day",3},{"Month",4},{"Year",5}};
public:
    LogSystem() {
        // Since operations is small, brute force search
        // is also fast.
    }
    
    void put(int id, string timestamp) {
        vp.push_back(make_pair(timestamp, id));
    }
    
    vector<int> retrieve(string s, string e, string gra) {
        vector<int> res;
        int n = dic[gra];
        s = s.substr(0, 19 - n*3), e = e.substr(0, 19 - n*3);
        for(int i = 0; i < n; i++) s += ":00", e += ":59";
        for(auto x: vp)
            if(x.first >= s && x.first <= e)
                res.push_back(x.second);
        return res;
    }
};

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem obj = new LogSystem();
 * obj.put(id,timestamp);
 * vector<int> param_2 = obj.retrieve(s,e,gra);
 */
