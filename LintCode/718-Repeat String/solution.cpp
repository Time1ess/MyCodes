class Solution {
public:
    /*
     * @param : string A to be repeated
     * @param : string B
     * @return: the minimum number of times A has to be repeated
     */
    int repeatedString(string &A, string &B) {
        // write your code here
        int len1 = A.length(), len2 = B.length();
        for(int i = 0; i < len1; i++) // try match from A[i]
        {
            bool match = true;
            int cnt = i == 0 ? 0 : 1;
            int k = i;
            for(int j = 0; j < len2; j++)
            {
                if(A[k] != B[j])
                {
                    match = false;
                    break;
                }
                if(k == 0)
                    cnt++;
                k = (k + 1) % len1;
            }
            if(match)
                return cnt;
        }
        return -1;
    }
};
