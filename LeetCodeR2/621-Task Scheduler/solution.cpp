class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> cnts(26, 0);
        for(auto c: tasks)
            cnts[c-'A']++;
        sort(cnts.begin(), cnts.end());
        int i = 25;
        int cnt = 0;
        while(i >= 0 && cnts[i--] == cnts[25])
            cnt++;
        return max((cnts[25] - 1) * (n + 1) + cnt, int(tasks.size()));
    }
};
