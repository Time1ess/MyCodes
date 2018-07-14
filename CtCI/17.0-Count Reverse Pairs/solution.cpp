class AntiOrder {
public:
    void merge(vector<int>& A, int& reverse_cnt, int s, int m, int e) {
        vector<int> tmp(A.size(), 0);
        int i = m - 1, j = e - 1, k = e - 1;
        while(i >= s && j >= m) {
            if(A[i] > A[j]) {
                reverse_cnt += j - m + 1;
                tmp[k--] = A[i--];
            } else {
                tmp[k--] = A[j--];
            }
        }
        while(i >= s) {
            tmp[k--] = A[i--];
        }
        while(j >= m) {
            tmp[k--] = A[j--];
        }
        for(int t = s; t < e; t++)
            A[t] = tmp[t];
    }
    void merge_sort(vector<int>& A, int& reverse_cnt, int s, int e) {
        if(s + 1 >= e)
            return;
        int m = s + (e - s) / 2;
        merge_sort(A, reverse_cnt, s, m);
        merge_sort(A, reverse_cnt, m, e);
        merge(A, reverse_cnt, s, m, e);
    }
    int count(vector<int> A, int n) {
        // write code here
        int ans = 0;
        merge_sort(A, ans, 0, n);
        return ans;
    }
};
