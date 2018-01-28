#include <iostream>
using namespace std;

int main()
{
    int a, b;
    cin>>a>>b;
    cout<<((a >= 0 && a <= 1024 && b >= 0 && b <= 1024) ? a == b : -1)<<endl;
    return 0;
}
