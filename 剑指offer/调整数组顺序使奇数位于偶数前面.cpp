#include <iostream>
#include <vector>

using namespace std;


bool is_odd(int x)
{
    return (x & 0x1) == 1;
}


void ReOrder(vector<int> &arr, bool (*front)(int))
{
    int size = arr.size();
    if(size <= 1)
        return;
    int l = 0, r = size - 1;
    while(l < r)
    {
        while(l < size && front(arr[l]))
            l++;
        while(r > 0 && !front(arr[r]))
            r--;
        if(l >= r)
            break;
        swap(arr[l], arr[r]);
    }
}


void ReOrderOddEven(vector<int> &arr)
{
    ReOrder(arr, is_odd);
}

int main()
{
    vector<int> arr{1, 8, 5, 2, 9, 6, 3, 7};
    ReOrderOddEven(arr);
    for(unsigned int i = 0; i < arr.size(); i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    return 0;
}
