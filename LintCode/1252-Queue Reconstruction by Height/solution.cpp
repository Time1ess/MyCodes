class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]);
    }
    /**
     * @param people: a random list of people
     * @return: the queue that be reconstructed
     */
    vector<vector<int>> reconstructQueue(vector<vector<int>> &people) {
        // write your code here
        sort(people.begin(), people.end(), cmp);
        vector<vector<int>> ans;
        int n = people.size();
        for(int i = 0; i < n; i++) {
            ans.insert(ans.begin() + people[i][1], people[i]);
        }
        return ans;
    }
};
