class Solution {
public:
    vector<int> partitionLabels(string S) {
        vector<int> ans;
        vector<int> indices(26, -1);
        int n = S.length();
        for (int i = 0; i < n; i++) {
            indices[S[i]-'a'] = i;
        }
        int len = 1;
        int last_idx = indices[S[0]-'a'];
        for (int i = 1; i < n; i++) {
            if (last_idx < i) {
                ans.push_back(len);
                len = 1;
                last_idx = indices[S[i]-'a'];
            } else {
                len++;
                last_idx = max(last_idx, indices[S[i]-'a']);
            }
        }
        ans.push_back(len);
        return ans;
    }
};
