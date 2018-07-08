class Finder {
public:
    int findElement(vector<int> A, int n, int x) {
        // write code here
        int l = 0, r = n;
        while(l < r) {
            int m = l + (r - l) / 2;
            if(A[m] == x)
                return m;
            else if(A[l] < A[m]) {
                if(A[l] <= x && x < A[m])
                    r = m;
                else
                    l = m + 1;
            } else {
                if(A[m] < x && x <= A[r-1])
                    l = m + 1;
                else
                    r = m;
            }
        }
        return l;
    }
};
