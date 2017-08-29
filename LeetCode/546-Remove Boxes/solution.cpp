// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-29 15:04
// Last modified: 2017-08-29 15:04
// Filename: solution.cpp
// Description:
class Solution {
public:
    int max_gain(vector<int>& boxes, int i, int j, int k, int dp[101][101][101])
    {
        // dp[i][j][k]: max gain from [i-th, j-th] with k boxes append to its left with same color as i-th box
        if(i > j)
            return 0;
        if(dp[i][j][k] > 0)
            return dp[i][j][k];
        while((i+1) <= j && boxes[i] == boxes[i+1])
            i++, k++;
        int gain = (k+1)*(k+1) + max_gain(boxes, i+1, j, 0, dp);  // Remove i-th, remaining [(i+1)-th, j-th] with k = 0
        for(int l = i + 1; l <= j; l++)
            if(boxes[l] == boxes[i])
                // Say l-th has the same color as i-th, we want to append i-th to l-th's left
                // Therefore, we first remove [(i+1)-th, (l-1)-th],
                // remaing [l, j] with k+1(previous k plus i-th) boxes has the same color as l-th box
                gain = max(gain, max_gain(boxes, i+1, l-1, 0, dp) + max_gain(boxes, l, j, k+1, dp));
        dp[i][j][k] = gain;
        return gain;
    }
    int removeBoxes(vector<int>& boxes) {
        int dp[101][101][101] = {{{0}}};
        return max_gain(boxes, 0, boxes.size()-1, 0, dp);
    }
};
