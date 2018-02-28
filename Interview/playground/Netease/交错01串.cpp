#include <iostream>
#include <string>

using namespace std;


int main()
{
    string s;
    cin>>s;
    int ans = 1;
    int current = 1;
    if(s.length() == 0)
    {
        cout<<0<<endl;
        return 0;
    }
    for(int i = 1; i < s.length(); i++)
    {
        if(s[i] != s[i-1])
            current++;
        else
            current = 1;
        ans = max(ans, current);
    }
    cout<<ans<<endl;
    return 0;
}
