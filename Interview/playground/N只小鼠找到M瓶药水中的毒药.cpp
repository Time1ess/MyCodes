#include <iostream>
#include <bitset>
#include <cstdlib>

using namespace std;

#define N 1000
#define M 10


int find_poisoned_bottle(bitset<N> &bottles)
{
    int k = 0;
    int half = 512;
    while(half)
    {
        bool found = false;
        for(int i = half; i < N; i += half * 2)
        {
            for(int j = i; j < i + half && j < N; j++)
                if(bottles[j] == true)
                {
                    k += half;
                    found = true;
                    break;
                }
            if(found)
                break;
        }
        half >>= 1;
    }
    return k;
}


int main()
{
    srand(time(0));
    bitset<N> bottles;
    int target_k = rand() % N;
    bottles[target_k] = true;
    int k = find_poisoned_bottle(bottles);
    cout<<target_k<<" "<<k<<endl;
    return 0;
}
