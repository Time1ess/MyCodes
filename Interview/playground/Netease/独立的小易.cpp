#include <iostream>

using namespace std;

int main()
{
    int x, f, d, p;
    cin>>x>>f>>d>>p;
    if(d / x < f)
    {
        cout<<d/x<<endl;
        return 0;
    }
    else
    {
        d -= f * x;
        cout<<f + d / (x + p)<<endl;
    }
    return 0;
}
