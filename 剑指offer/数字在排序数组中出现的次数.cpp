#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int lower(vector<int> &data, int s, int e, int t)
    {
        while(s <= e)
        {
            int m = s + (e - s) / 2;
            if(data[m] == t)
            {
                if(m == 0 || m > 0 && data[m-1] != t)
                    return m;
                else
                    e = m - 1;
            }
            else if(data[m] > t)
                e = m - 1;
            else
                s = m + 1;
        }
        if(s > e)
            return -1;
        return s;
    }
    int upper(vector<int> &data, int s, int e, int t)
    {
        int size = data.size();
        while(s <= e)
        {
            int m = s + (e - s) / 2;
            if(data[m] == t)
            {
                if(m == size - 1 || m < size - 1 && data[m+1] != t)
                    return m;
                else
                    s = m + 1;
            }
            else if(data[m] < t)
                s = m + 1;
            else
                e = m - 1;
        }
        if(s > e)
            return -1;
        return s;
    }
    int GetNumberOfK(vector<int> data ,int k) {
        int size = data.size();
        if(size == 0)
            return 0;
        int lb = lower(data, 0, size - 1, k);
        int ub = upper(data, 0, size - 1, k);
        if(lb != -1 && ub != -1)
        	return ub - lb + 1;
        return 0;
    }
};

int main()
{
    vector<int> s{1,3,3,3,3,4,5};
    Solution sol;
    cout<<sol.GetNumberOfK(s, 2)<<endl;
    return 0;
}
