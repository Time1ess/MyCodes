#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> nums;
    int n;
    cin>>n;
    if(n <= 2)
    {
        cout<<"Possible"<<endl;
        return 0;
    }
    for(int i = 0; i < n; i++)
    {
        int x;
        cin>>x;
        nums.push_back(x);
    }
    sort(nums.begin(), nums.end());
    bool possible = true;
    for(int i = 2; i < n; i++)
    {
        if(nums[i-1] - nums[i-2] != nums[i] - nums[i-1])
        {
            possible = false;
            break;
        }
    }
    if(possible)
        cout<<"Possible"<<endl;
    else
        cout<<"Impossible"<<endl;
    return 0;
}
