#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<int> nums;
    for(int i = 0; i < n; i++)
    {
        int x;
        cin>>x;
        nums.push_back(x);
    }
    if(n == 1)
    {
        cout<<nums[0]<<endl;
        return 0;
    }
    else if(n == 2)
    {
        cout<<nums[1]<<" "<<nums[0]<<endl;
        return 0;
    }
    int l, r;
    r = n - 1;
    l = (n & 0x1) ? 1 : 0;
    for(int i = r; i >= 0; i -= 2)
        cout<<nums[i]<<" ";
    for(int i = l; i < n - 2; i += 2)
        cout<<nums[i]<<" ";
    cout<<nums[n-2]<<endl;
    return 0;
}
