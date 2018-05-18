class Solution {
public:
    /**
     * @param n: Given the range of numbers
     * @param k: Given the numbers of combinations
     * @return: All the combinations of k numbers out of 1..n
     */
    void generate_combinations(vector<vector<int>> &ans, vector<int> &current,
                               int s, int e, int k)
    {
        if(k == 0)
        {
            ans.push_back(current);
            return;
        }
        if(e - s + 1 < k)
            return;
        current.push_back(s);
        generate_combinations(ans, current, s + 1, e, k - 1);
        current.pop_back();
        generate_combinations(ans, current, s + 1, e, k);
    }
    vector<vector<int>> combine(int n, int k) {
        // write your code here
        vector<vector<int>> ans;
        vector<int> current;
        generate_combinations(ans, current, 1, n, k);
        return ans;
    }
};
