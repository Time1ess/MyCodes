class Solution {
public:
    /**
     * @param sentence: a list of string
     * @param rows: an integer
     * @param cols: an integer
     * @return: return an integer, denote times the given sentence can be fitted on the screen
     */
    int wordsTyping(vector<string> &sentence, int rows, int cols) {
        // Write your code here
        int cnt = 0;
        int n = sentence.size();
        int k = 0;
        int len = sentence[k].length();
        for(int i = 0; i < rows; i++)
        {
            int space = cols;
            while(k < n && len <= space)
            {
                space -= (len + 1);
                k++;
                if(k == n)
                {
                    k = 0;
                    cnt++;
                }
                len = sentence[k].length();
            }
        }
        return cnt;
    }
};
