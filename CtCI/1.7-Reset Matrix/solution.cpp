class Clearer {
public:
    vector<vector<int> > clearZero(vector<vector<int> > mat, int n) {
        // write code here
        vector<bool> rows(n, false), cols(n, false);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(mat[i][j] == 0) {
                    rows[i] = true;
                    cols[j] = true;
                }
        for(int i = 0; i < n; i++)
            if(rows[i] == true)
                for(int j = 0; j < n; j++)
                    mat[i][j] = 0;
        for(int j = 0; j < n; j++)
            if(cols[j] == true)
                for(int i = 0; i < n; i++)
                    mat[i][j] = 0;
        return mat;
    }
};
