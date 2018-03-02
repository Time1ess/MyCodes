bool cmp(const pair<int, double> &a, const pair<int, double> &b)
{
    return a.first < b.first;
}
class Solution {
public:
    /**
     * @param n an integer
     * @return a list of pair<sum, probability>
     */
    vector<pair<int, double>> dicesSum(int n) {
        // Write your code here
        vector<pair<int, double>> ans;
        unordered_map<int, long long> sums;
        for(int i = 1; i <= 6; i++)
            sums[i] = 1;
        for(int i = 1; i < n; i++)
        {
            unordered_map<int, long long> tmp_sums;
            for(auto x: sums)
            {
                for(int i = 1; i <= 6; i++)
                    tmp_sums[x.first+i] += x.second;
            }
            sums = tmp_sums;
        }
        long long total = 0;
        for(auto p: sums)
            total += p.second;
        for(auto p: sums)
            ans.push_back({p.first, (double)p.second / total});
        sort(ans.begin(), ans.end(), cmp);
        return ans;
    }
};
