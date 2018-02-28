#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<int> students;
    int t;
    for(int i = 0; i < n; i++)
    {
        cin>>t;
        students.push_back(t);
    }
    if(n == 1)
    {
        cout<<0<<endl;
        return 0;
    }
    else if(n == 2)
    {
        cout<<abs(students[0] - students[1])<<endl;
        return 0;
    }
    sort(students.begin(), students.end());
    int l = 0, r = n - 1;
    int ans = 0;
    int left_val, right_val;
    left_val = right_val = students[r--];
    bool left = false;
    while(l <= r)
    {
        if(!left)
        {
            ans += abs(right_val - students[l]);
            right_val = students[l++];
            if(l <= r)
            {
                ans += abs(right_val - students[r]);
                right_val = students[r--];
            }
        }
        else
        {
            ans += abs(left_val - students[l]);
            left_val = students[l++];
            if(l <= r)
            {
                ans += abs(left_val - students[r]);
                left_val = students[r--];
            }
        }
        left = !left;
    }
    cout<<ans<<endl;
    return 0;
}
