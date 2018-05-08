class Solution {
public:
    /*
     * @param source: source string to be scanned.
     * @param target: target string containing the sequence of characters to match
     * @return: a index to the first occurrence of target in source, or -1  if target is not part of source.
     */
    vector<int> calculate_next(const char *target, int n)
    {
        vector<int> next(n, -1);
        int k = -1;
        for(int q = 1; q < n; q++)
        {
            while(k > -1 && target[k+1] != target[q])
                k = next[k];
            if(target[k+1] == target[q])
                k++;
            next[q] = k;
        }
        return next;
    }
    int strStr(const char *source, const char *target) {
        // write your code here
        if(source == NULL || target == NULL)
            return -1;
        int n = strlen(target);
        int m = strlen(source);
        if(n > m)
            return -1;
        else if(n == m)
            return strcmp(source, target) == 0 ? 0 : -1;
        else if(*target == '\0')
            return 0;
        vector<int> next = calculate_next(target, n);
        int k = -1;
        for(int i = 0; i < m; i++)
        {
            while(k > -1 && target[k+1] != source[i])
                k = next[k];
            if(target[k+1] == source[i])
                k++;
            if(k == n - 1)
            {
                return i - n + 1;
            }
        }
        return -1;
    }
};
