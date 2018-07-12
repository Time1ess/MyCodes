class Solution {
public:
    /**
     * @param licensePlate: a string
     * @param words: List[str]
     * @return: return a string
     */
    vector<int> cntChars(const string& s) {
        vector<int> cnt(26, 0);
        for(auto x: s) {
            if(x >= 'a' && x <= 'z')
                cnt[x-'a']++;
            else if(x >= 'A' && x <= 'Z')
                cnt[x-'A']++;
        }
        return cnt;
    }
    bool cntMatch(const vector<int>& cnt1, const vector<int>& cnt2) {
        for(int i = 0; i < 26; i++)
            if(cnt1[i] < cnt2[i])
                return false;
        return true;
    }
    string shortestCompletingWord(string &licensePlate, vector<string> &words) {
        // write your code here
        vector<int> targetCnts = cntChars(licensePlate);
        int idx = -1;
        int n = words.size();
        for(int i = 0; i < n; i++) {
            vector<int> realCnts = cntChars(words[i]);
            if(cntMatch(realCnts, targetCnts)
                && (idx == -1 || words[idx].length() > words[i].length()))
                idx = i;
        }
        return words[idx];
    }
};
