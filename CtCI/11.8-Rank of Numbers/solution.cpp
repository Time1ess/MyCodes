class Rank {
public:
    vector<int> getRankOfNumber(vector<int> A, int n) {
        // write code here
        vector<int> sorted;
        vector<int> ans;
        for(auto x : A) {
            auto it = upper_bound(sorted.begin(), sorted.end(), x);
            ans.push_back(it - sorted.begin());
            sorted.insert(it, x);
        }
        return ans;
    }
};
