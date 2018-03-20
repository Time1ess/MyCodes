class Solution {
public:
    /**
     * @param A: lists A
     * @param B: lists B
     * @return: the index mapping
     */
    vector<int> anagramMappings(vector<int> &A, vector<int> &B) {
        // Write your code here
        unordered_map<int, vector<int>> positions;
        for(int i = 0; i < B.size(); i++)
            positions[B[i]].push_back(i);
        vector<int> ans;
        for(int i = 0; i < A.size(); i++)
        {
            ans.push_back(positions[A[i]].back());
            positions[A[i]].pop_back();
        }
        return ans;
    }
};
