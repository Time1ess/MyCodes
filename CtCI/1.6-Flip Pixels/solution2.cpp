class Transform {
public:
    vector<vector<int> > transformImage(vector<vector<int> > mat, int n) {
        for(int l = 0; l < n / 2; l++) {
            int first = l;
            int last = n - l - 1;
            for(int x = first; x < last; x++) {
                int offset = x - first;
                int tmp = mat[first][x];
                mat[first][x] = mat[last - offset][first];
                mat[last - offset][first] = mat[last][last - offset];
                mat[last][last - offset] = mat[x][last];
                mat[x][last] = tmp;
            }
        }
        return mat;
    }
};
