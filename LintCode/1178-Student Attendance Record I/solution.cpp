class Solution {
public:
    /**
     * @param s: a string
     * @return: whether the student could be rewarded according to his attendance record
     */
    bool checkRecord(string &s) {
        // Write your code here
        bool reward = true;
        int lateCnt = 0;
        bool absent = false;
        for(auto c: s) {
            if (c == 'A') {
                if(absent)
                    return false;
                absent = true;
                lateCnt = 0;
            } else if (c == 'L') {
                lateCnt++;
                if(lateCnt > 2)
                    return false;
            } else if (c == 'P') {
                lateCnt = 0;
            }
        }
        return true;
    }
};
