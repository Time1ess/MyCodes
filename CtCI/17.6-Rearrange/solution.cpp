class Rearrange {
public:
    int find_end_idx(vector<int>& A, int n) {
        for(int i = 1; i < n; i++) {
            if(A[i] < A[i-1]) {
                return i - 1;
            }
        }
        return n - 1;
    }
    int find_start_idx(vector<int>& A, int n) {
        for(int i = n - 2; i >= 0; i--) {
            if(A[i] > A[i+1]) {
                return i + 1;
            }
        }
        return 0;
    }
    int adjust_left(vector<int>& A, int s, int target) {
        while(s >= 0 && A[s] > A[target]) {
            s--;
        }
        return s + 1;
    }
    int adjust_right(vector<int>& A, int e, int target, int n) {
        while(e < n && A[e] < A[target])
            e++;
        return e - 1;
    }
    vector<int> findSegment(vector<int> A, int n) {
        // write code here
        int end_left = find_end_idx(A, n);
        int start_right = find_start_idx(A, n);
        
        int min_idx = end_left + 1;
        if(min_idx == n)
            return {0, 0};
        
        int max_idx = start_right - 1;
        for(int i = end_left; i <= start_right; i++) {
            if(A[i] > A[max_idx]) {
                max_idx = i;
            }
            if(A[i] < A[min_idx]) {
                min_idx = i;
            }
        }
        
        // Adjust left and right to make sure the range contains all elements in the middle part
        int l = adjust_left(A, end_left, min_idx);
        int r = adjust_right(A, start_right, max_idx, n);
        return {l, r};
    }
};
