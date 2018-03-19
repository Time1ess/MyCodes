class Solution {
public:
    /**
     * @param time: the given time
     * @return: the next closest time
     */
    string nextClosestTime(string &time) {
        // write your code here
        int hour = (time[0] - '0') * 10 + time[1] - '0';
        int minute = (time[3] - '0') * 10 + time[4] - '0';
        bool allows[10] = {false};
        allows[hour/10] = allows[hour%10] = true;
        allows[minute/10] = allows[minute%10] = true;
        for(int h = hour; h < 24; h++)
            for(int m = 0; m < 60; m++)
                if(h == hour && m <= minute)
                    continue;
                else if(allows[h/10] && allows[h%10] && allows[m/10] && allows[m%10])
                    return (h < 10 ? "0": "") + to_string(h) + ":"
                        + (m < 10 ? "0" : "") + to_string(m);
        for(int h = 0; h <= hour; h++)
            for(int m = 0; m <= 60; m++)
                if(allows[h/10] && allows[h%10] && allows[m/10] && allows[m%10])
                    return (h < 10 ? "0": "") + to_string(h) + ":"
                        + (m < 10 ? "0" : "") + to_string(m);
    }
};
