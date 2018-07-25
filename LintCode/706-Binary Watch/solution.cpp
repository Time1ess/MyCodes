class Solution {
public:
    /**
     * @param num: the number of "1"s on a given timetable
     * @return: all possible time
     */
    int count_ones(int x) {
        int cnt = 0;
        while(x) {
            x &= (x-1);
            cnt++;
        }
        return cnt;
    }
    string format_time(int h, int m) {
        return to_string(h) + ":" + (m < 10 ? "0": "") + to_string(m);
    }
    vector<string> binaryTime(int num) {
        // Write your code here
        vector<string> ans;
        for(int h = 0; h < 12; h++) {
            for(int m = 0; m < 60; m++) {
                if(count_ones(h) + count_ones(m) == num) {
                    ans.push_back(format_time(h, m));
                }
            }
        }
        return ans;
    }
};
