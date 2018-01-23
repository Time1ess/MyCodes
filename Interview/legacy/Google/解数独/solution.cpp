#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool check_valid(vector<vector<int>> sudoku, int i, int j, int target)
    {
        for(int _i = 0; _i < 9; _i++)
            if(sudoku[_i][j] == target)
                return false;
        for(int _j = 0; _j < 9; _j++)
            if(sudoku[i][_j] == target)
                return false;
        int src_r = i / 3 * 3;
        int src_c = j / 3 * 3;
        for(int _r = src_r; _r < src_r + 3; _r++)
            for(int _c = src_c; _c < src_c + 3; _c++)
                if(sudoku[_r][_c] == target)
                    return false;
        return true;
    }
    unsigned short get_valid_nums(vector<vector<int>> &sudoku, int i, int j)
    {
        unsigned short valid_nums = 0;
        for(int k = 1; k <= 9; k++)
            if(check_valid(sudoku, i, j, k))
                valid_nums |= 1 << (k - 1);
        return valid_nums;
    }
    bool dfs(vector<vector<int>> &sudoku, vector<vector<int>> &ans, int i, int j, int &row, int &col)
    {
        unsigned short valid_nums = get_valid_nums(sudoku, i, j);
        if((i == row-1 && j == col - 1) || (sudoku[i][j] == 0 && valid_nums == 0))
        {
            if(i == row - 1 && j == col - 1)
            {
                ans = sudoku;
                return true;
            }
            return false;
        }
        if(sudoku[i][j] != 0)
        {
            if(j < 8)
                return dfs(sudoku, ans, i, j+1, row, col);
            else
                return dfs(sudoku, ans, i+1, 0, row, col);
        }
        for(int k = 1; k <= 9; k++)
        {
            bool found = false;
            if(!(valid_nums & (1 << (k-1))))
                continue;
            sudoku[i][j] = k;
            if(j < 8)
                found = dfs(sudoku, ans, i, j+1, row, col);
            else
                found = dfs(sudoku, ans, i+1, 0, row, col);
            if(found)
                return true;
            sudoku[i][j] = 0;
        }
        return false;
    }
    vector<vector<int>> solve_sudoku(vector<vector<int>> sudoku)
    {
        vector<vector<int>> ans;
        int row = sudoku.size();
        int col = sudoku[0].size();
        bool found = dfs(sudoku, ans, 0, 0, row, col);
        if(found)
            cout<<"Found"<<endl;
        else
            cout<<"Not Found"<<endl;
        return ans;
    }
};


int main()
{
    vector<vector<int>> sudoku{
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,2,0,0,9,0,4},
        {0,8,3,1,0,0,0,0,2},
        {0,0,0,9,0,0,4,0,6},
        {0,2,0,3,0,5,0,9,0},
        {3,0,9,0,0,7,0,0,0},
        {4,0,0,0,0,9,3,1,0},
        {5,0,8,0,0,4,0,0,0},
        {0,0,0,0,0,0,0,0,0}};
    vector<vector<int>> sudoku2{
        {4,0,0,0,1,5,6,0,3},
        {0,0,0,0,0,8,9,0,0},
        {3,7,5,0,4,0,8,0,0},
        {7,8,0,0,0,0,0,0,0},
        {1,0,4,0,0,0,3,0,7},
        {0,0,0,0,0,0,0,5,2},
        {0,0,9,0,2,0,7,3,4},
        {0,0,7,1,0,0,0,0,0},
        {8,0,6,5,3,0,0,0,9},
    };
    Solution sol;
    vector<vector<int>> ans = sol.solve_sudoku(sudoku);
    int row = ans.size();
    int col = ans[0].size();
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
            cout<<ans[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}
