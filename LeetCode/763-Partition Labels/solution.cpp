class Solution {
public:
    vector<int> partitionLabels(string S) {
        vector<int> ans;
        vector<int> nexts(S.length(), -1);
        unordered_map<char, int> last_idx;
        for(int i = S.length() -1; i >= 0; i--)
        {
            nexts[i] = last_idx.find(S[i]) == last_idx.end() ? -1 : last_idx[S[i]];
            last_idx[S[i]] = i;
        }
        int maximum;
        int s = 0, start;
        while(s < S.length())
        {
            start = s;
            maximum = s + 1;
            while(s < maximum)
            {
                maximum = max(maximum, nexts[s] + 1);
                s++;
            }
            ans.push_back(maximum - start);
        }
        return ans;
    }
};
