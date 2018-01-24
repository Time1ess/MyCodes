#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        vector<vector<int>> ans;
        if(sum <= 2)
            return ans;
        int max_k = (int)sqrt(2 * sum);
        for(int k = max_k; k >= 2; k--)
        {
            if((2 * sum - k * k + k) % (2 * k) == 0)
            {
                vector<int> tmp;
                int x = (2 * sum - k * k + k) / (2 * k);
                for(int i = 0; i < k; i++)
                    tmp.push_back(x + i);
                ans.push_back(tmp);
            }
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> ans;
    ans = sol.FindContinuousSequence(9);
    for(int i = 0; i < ans.size(); i++)
    {
        for(int j = 0; j < ans[i].size(); j++)
            cout<<ans[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}
