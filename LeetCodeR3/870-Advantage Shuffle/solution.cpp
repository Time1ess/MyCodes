bool cmp(const pair<int, int>& pa, const pair<int, int>& pb) {
    return pa.first < pb.first;
}
class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        vector<pair<int, int>> pa, pb;
        int n = A.size();
        for (int i = 0; i < n; i++) {
            pa.push_back({A[i], i});
            pb.push_back({B[i], i});
        }
        sort(pa.begin(), pa.end(), cmp);
        sort(pb.begin(), pb.end(), cmp);
        vector<int> ans(n, -1);
        vector<int> abandon;
        int i = 0, j = 0;
        while (i < n && j < n) {
            if (pa[i].first > pb[j].first) {
                ans[pb[j].second] = pa[i].first;
                j++;
            } else {
                abandon.push_back(pa[i].first);
            }
            i++;
        }
        for (int i = 0; i < n; i++) {
            if (ans[i] == -1) {
                ans[i] = abandon.back();
                abandon.pop_back();
            }
        }
        return ans;
    }
};
