#include <iostream>
#include <vector>
using namespace std;


int main()
{
    vector<int> s{1,1,1,1,2,1,1,2,2,2,2,2,3,4,4,4,4,4,4};
    int ones, twos, threes, mask;
    ones = twos = threes = 0, mask = 0;
    for(auto x: s)
    {
        threes ^= twos & ones & x;
        twos ^= ones & x;
        ones ^= x;
        mask = ~(ones & ~twos & threes);
        threes &= mask;
        twos &= mask;
        ones &= mask;
    }
    cout<<twos<<endl;
    return 0;
}
