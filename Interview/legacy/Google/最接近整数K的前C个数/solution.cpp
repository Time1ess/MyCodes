#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;


class Solution
{
public:
    int partition(vector<int> &s, int start, int end, int k)
    {
        int index = rand() % (end - start) + start;
        swap(s[index], s[end]);
        int small = start - 1;
        for(int i = start; i < end; i++)
        {
            if(abs(s[i]-k) < abs(s[end]-k) && i != ++small)
                swap(s[i], s[small]);
        }
        ++small;
        swap(s[small], s[end]);
        return small;
    }

    void quick_sort(vector<int> &s, int start, int end, int c, int k)
    {
        if(start >= end || c == 0)
            return;
        int index = partition(s, start, end, k);  // How many elems that are closer to k than s[index]
        if(index == c)  // Exact c elems, no need furthur
            return;
        else if(index > c)  // More than c elems, need to continue
            quick_sort(s, start, index - 1, c, k);
        else  // Less than c elems, need to select from second part
            quick_sort(s, index + 1, end, c - index - 1, k);
    }
    vector<int> ClosestNumbers(vector<int> s, int k, int c)
    {
        vector<int> ans;
        int size = s.size();
        if(size == 0)
            return ans;
        quick_sort(s, 0, size - 1, c, k);
        for(int i = 0; i < c; i++)
            ans.push_back(s[i]);
        return ans;
    }
};


int main()
{
    vector<int> s{1,9,8,5,4,6,7,3};
    Solution sol;
    vector<int> ans = sol.ClosestNumbers(s, 3, 4);
    for(auto x: ans)
        cout<<x<<endl;
    sort(s.begin(), s.end());
    for(auto x: s)
        cout<<x<<" ";
    cout<<endl;
    return 0;
}
