class Solution {
public:
    /**
     * @param m: an integer
     * @param n: an integer
     * @return: the total number of unlock patterns of the Android lock screen
     */
     
    void dfs(vector<bool> &selected, vector<vector<int>> &cons, 
             int &ans, int current, int last,
             int min_keys, int max_keys)
    {
        if(current == max_keys)
        {
            ans++;
            return;
        }
        if(current >= min_keys)
            ans++;
        for(int i = 1; i <= 9; i++)
        {
            if(selected[i]) // Already selected
                continue;
            if(cons[last][i] != 0 && !selected[cons[last][i]])
                continue;
            selected[i] = true;
            dfs(selected, cons, ans, current+1, i, min_keys, max_keys);
            selected[i] = false;
        }
    }
    int numberOfPatterns(int m, int n) {
        // Write your code here
        vector<bool> selected(9, false);
        vector<vector<int>> cons(10, vector<int>(10, 0));
        cons[1][3] = cons[3][1] = 2;  
        cons[1][7] = cons[7][1] = 4;  
        cons[3][9] = cons[9][3] = 6;  
        cons[7][9] = cons[9][7] = 8;  
        cons[2][8] = cons[8][2] = cons[4][6] = cons[6][4] = 5;  
        cons[1][9] = cons[9][1] = cons[3][7] = cons[7][3] = 5;  
        int ans = 0;
        for(int i = 1; i <= 9; i++)
        {
            selected[i] = true;
            dfs(selected, cons, ans, 1, i, m, n);
            selected[i] = false;
        }
        return ans;
    }
};
