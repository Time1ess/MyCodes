class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int size_a = A.size(), size_b = B.size();
        int max_len = 0;
        for(int i = 0; i < size_a; i++)
        {
            int cur_len = 0;
            for(int k = i, j = 0; k < size_a && j < size_b; k++, j++)
            {
                if(A[k] != B[j])
                    cur_len = 0;
                else
                {
                    cur_len++;
                    max_len = max(max_len, cur_len);
                }
            }
        }
        for(int j = 0; j < size_b; j++)
        {
            int cur_len = 0;
            for(int k = j, i = 0; k < size_b && i < size_a; k++, i++)
            {
                if(A[i] != B[k])
                    cur_len = 0;
                else
                {
                    cur_len++;
                    max_len = max(max_len, cur_len);
                }
            }
        }
        return max_len;
    }
};
