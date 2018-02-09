class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int n = row.size();
        vector<int> pos(n, 0);
        for(int i = 0; i < n; i++)
            pos[row[i]] = i;
        int cnt = 0;
        for(int i = 0; i < n; i += 2)
        {
            int j = row[i] % 2 == 0 ? row[i] + 1 : row[i] - 1;
            if(row[i+1] != j)
            {
                row[pos[j]] = row[i+1];
                pos[row[i+1]] = pos[j];
                row[i+1] = j;
                pos[j] = i+1;
                cnt++;
            }
        }
        return cnt;
    }
};
