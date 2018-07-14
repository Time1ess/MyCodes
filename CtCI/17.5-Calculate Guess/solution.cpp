class Result {
public:
    vector<int> calcResult(string A, string guess) {
        // write code here
        vector<int> cnt(26, 0);
        vector<int> ans(2, 0);
        for(int i = 0; i < 4; i++) {
            if(A[i] == guess[i]) {
                ans[0]++;
            } else {
                cnt[A[i]-'A']++;
            }
        }
        for(int i = 0; i < 4; i++) {
            if(A[i] == guess[i]) {
                continue;
            }
            if(cnt[guess[i]-'A'] > 0) {
                cnt[guess[i]-'A']--;
                ans[1]++;
            }
        }
        return ans;
    }
};
