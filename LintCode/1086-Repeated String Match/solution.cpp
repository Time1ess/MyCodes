class Solution {
public:
    /**
     * @param A: a string
     * @param B: a string
     * @return: return an integer
     */
    int repeatedStringMatch(string &A, string &B) {
        // write your code here
        int m = A.length();
        int n = B.length();
        int i = 0, j = 0;
        int cnt = 0;
        while(j < n && i < m) {
            if (B[j] == A[i]) {
                if(j == 0 && i != 0)
                    cnt++;
                if(i == 0)
                    cnt++;
                j++;
                i = (i + 1) % m;
                continue;
            }
            cnt = 0;
            j = 0;
            i++;  // try next pos;
        }
        return cnt == 0 ? -1 : cnt;
    }
};
