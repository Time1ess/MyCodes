class Solution {
public:
    /**
     * @param setList: The input set list
     * @return: the cartesian product of the set list
     */
    void backtracking(vector<vector<int>> &ans, vector<int> &current,
                      vector<vector<int>> &setList, int set_idx)
    {
        int n = setList.size();
        if(set_idx == n)
        {
            ans.push_back(current);
            return;
        }
        int m = setList[set_idx].size();
        for(int i = 0; i < m; i++)
        {
            current.push_back(setList[set_idx][i]);
            backtracking(ans, current, setList, set_idx+1);
            current.pop_back();
        }
    }
    vector<vector<int>> getSet(vector<vector<int>> &setList) {
        // Write your code here
        vector<vector<int>> ans;
        vector<int> current;
        backtracking(ans, current, setList, 0);
        return ans;
    }
};
