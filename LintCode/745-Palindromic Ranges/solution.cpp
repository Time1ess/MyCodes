class Solution {
public:
    /**
     * @param L: A positive integer
     * @param R: A positive integer
     * @return: the number of interesting subranges of [L, R]
     */
    bool is_palindromic(string s)
    {
        int i = 0, j = s.size() - 1;
        while(i < j)
            if(s[i++] != s[j--])
                return false;
        return true;
    }
    int PalindromicRanges(int L, int R) {
        // Write your code here
        vector<int> is_palindrome;
        for(int x = L; x <= R; x++)
            if(is_palindromic(to_string(x)))
                is_palindrome.push_back(1);
            else
                is_palindrome.push_back(0);
        int cnt = 0;
        int t;
        for(int l1 = L; l1 <= R; l1++)
        {
            t = 0;
            for(int r1 = l1; r1 <= R; r1++)
            {
                t += is_palindrome[r1 - L];
                if((t & 0x1) == 0)
                    cnt++;
            }
        }
        return cnt;
    }
};
