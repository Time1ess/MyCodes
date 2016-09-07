#include <vector>
#include <math>
class Solution {
public:
    bool conflict(int next_x,vector<int> &state)
    {
        int next_y=state.size();
        for(int i=0;i<next_y;i++)
        {
            if(abs(next_x-state[i])==0||abs(next_x-state[i])==(next_y-i))
            return true;
        }
        return false;
    }
    int queens(int n,vector<int> &state)
    {
        int ans_cnt=0;
        for(int i=0;i<n;i++)
        {
            if(!conflict(i,state))
            {
                if(state.size()==n-1)
                {
                    return 1;
                }
                else
                {
                    state.push_back(i);
                    ans_cnt+=queens(n,state);
                    state.pop_back();
                }
            }
        }
        return ans_cnt;
    }
    int totalNQueens(int n) {
        int ans_cnt=0;
        vector<int> state;
        ans_cnt=queens(n,state);
        return ans_cnt;
    }
};
