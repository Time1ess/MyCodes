class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        unordered_map<int, bool> times;
        int min_time = INT_MAX, max_time = INT_MIN;
        for(auto x: timePoints)
        {
            int t = 60 * ((x[0] - '0') * 10 + x[1] - '0') + (x[3] - '0') * 10 + x[4] - '0';
            if(times[t] == true)
                return 0;
            times[t] = true;
            min_time = min(min_time, t);
            max_time = max(max_time, t);
        }
        int last = -1440;
        int min_diff = min(max_time - min_time, 1440 - max_time + min_time);
        for(int i = 0; i < 1440; i++)
        {
            if(times.find(i) != times.end())
            {
                min_diff = min(min_diff, i - last);
                last = i;
            }
        }
        return min_diff;
    }
};
