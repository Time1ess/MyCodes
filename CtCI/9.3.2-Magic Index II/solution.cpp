class MagicIndex {
public:
    bool findMagicIndex(vector<int>& A, int s, int e) {
        if(s >= e)
            return false;
        
        int m = s + (e - s) / 2;
        if(A[m] == m)
            return true;
        
        return findMagicIndex(A, s, min(m-1, A[m])) || findMagicIndex(A, max(m+1, A[m]), e);
    }
    bool findMagicIndex(vector<int> A, int n) {
        // write code here
        return findMagicIndex(A, 0, n);
    }
};
