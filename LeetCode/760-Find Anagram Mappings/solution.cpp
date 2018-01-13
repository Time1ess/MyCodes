class Solution {
public:
    vector<int> anagramMappings(vector<int>& A, vector<int>& B) {
        unordered_map<int, int> positions;
        for(int i = 0; i < B.size(); i++)
            positions[B[i]] = i;
        vector<int> ans;
        for(int i = 0; i < A.size(); i++)
            ans.push_back(positions[A[i]]);
        return ans;
    }
};
