class Solution {
public:
    void backtracking(vector<string> &ans, int hour, int minute, int ih, int im, int cnt)
    {
        if(hour >= 12 || minute >= 60)
            return;
        if(cnt == 0)
        {
            ans.push_back(to_string(hour) + ":" + (minute < 10 ? "0": "") + to_string(minute));
            return;
        }
        if(ih < 4)
        {
            backtracking(ans, hour | (1 << (3-ih)), minute, ih + 1, im, cnt-1);
            backtracking(ans, hour, minute, ih + 1, im, cnt);
        }
        else if(im < 6)
        {
            backtracking(ans, hour, minute | (1 << (5 - im)), ih, im + 1, cnt-1);
            backtracking(ans, hour, minute, ih, im + 1, cnt);
        }
    }
    vector<string> readBinaryWatch(int num) {
        vector<string> ans;
        backtracking(ans, 0, 0, 0, 0, num);
        return ans;
    }
};
