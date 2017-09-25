// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-25 09:07
// Last modified: 2017-09-25 09:07
// Filename: solution.cpp
// Description:
class Solution {
public:
    int cal_dist(string src, string dst)
    {
        if(src == dst)
            return 34560;
        int dist = 0;
        dist += (dst[0] - src[0]) * 600;
        dist += (dst[1] - src[1]) * 60;
        dist += (dst[3] - src[3]) * 10 + dst[4] - src[4];
        if(dist < 0)
            dist += 1440;
        return dist;
    }
    string nextClosestTime(string time) {
        set<char> digits_set;
        for(auto x: time)
            if(x != ':')
                digits_set.insert(x);
        vector<char> digits(digits_set.begin(), digits_set.end());
        string cand = "00:00";
        string ans;
        int min_dist = INT_MAX, dist;
        for(auto h1: digits)
            for(auto h2: digits)
                for(auto m1: digits)
                    for(auto m2: digits)
                    {
                        if(h1 > '2' || (h1 == '2' && h2 >= '4') || m1 > '5')
                            continue;
                        cand[0] = h1;
                        cand[1] = h2;
                        cand[3] = m1;
                        cand[4] = m2;
                        dist = cal_dist(time, cand);
                        if(dist < min_dist)
                        {
                            min_dist = dist;
                            ans = cand;
                        }
                    }
        return ans;
    }
};
