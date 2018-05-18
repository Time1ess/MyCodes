class Solution {
public:
    /**
     * @param candidates: A list of integers
     * @param target: An integer
     * @return: A list of lists of integers
     */
    void combinations(vector<vector<int>> &ans, vector<int> &current,
                      vector<int> &candidates, int s, int e, int target)
    {
        if(target == 0)
        {
            ans.push_back(current);
            return;
        }
        if(s == e || candidates[s] > target)
            return;
        current.push_back(candidates[s]);
        combinations(ans, current, candidates, s, e, target - candidates[s]);
        current.pop_back();
        combinations(ans, current, candidates, s + 1, e, target);
    }
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        // write your code here
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans;
        vector<int> current;
        combinations(ans, current, candidates, 0, candidates.size(), target);
        return ans;
    }
};
