class MagicIndex {
public:
    bool findMagicIndex(vector<int> A, int n) {
        int l = 0, r = n;
        while(l < r) {
            int m = l + (r - l) / 2;
            if(A[m] == m)
                return true;
            else if(A[m] > m)
                r = m;
            else
                l = m + 1;
        }
        return false;
    }
};
