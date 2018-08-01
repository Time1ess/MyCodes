bool cmp(const pair<int, int>& p1, const pair<int, int>& p2) {
    return p1.first > p2.first || (p1.first == p2.first && p1.second < p2.second);
}
class Solution {
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        sort(people.begin(), people.end(), cmp);
        vector<pair<int, int>> ans;
        for(auto x: people) {
            ans.insert(ans.begin() + x.second, x);
        }
        return ans;
    }
};
