class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> apb;
        int n = A.size();
        if(n == 0)
            return 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                apb[A[i]+B[j]]++;
        int cnt = 0;
        for(int k = 0; k < n; k++)
            for(int l = 0; l < n; l++)
                cnt += apb[-(C[k]+D[l])];
        return cnt;
    }
};
