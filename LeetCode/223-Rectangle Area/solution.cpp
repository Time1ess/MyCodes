// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-05 14:35
// Last modified: 2017-09-05 14:35
// Filename: solution.cpp
// Description:
class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int sum = (C-A) * (D-B) + (G-E) * (H-F);
        if(B >= H || F >= D || A >= G || E >= C)
            return sum;
        int lbx = max(A, E), lby = max(B, F);
        int rtx = min(C, G), rty = min(D, H);
        return sum - (rtx-lbx) * (rty-lby);
    }
};
