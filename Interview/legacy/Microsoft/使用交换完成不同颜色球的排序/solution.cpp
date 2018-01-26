#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;


void swap(vector<char> &ans, int &front, int end, char target)
{
    int size = ans.size();
    while(front < end)
    {
        while(front < size && ans[front] == target)
            front++;
        while(end >= 0 && ans[end] != target)
            end--;
        if(front >= end)
            break;
        swap(ans[front], ans[end]);
    }
}

vector<char> sort_array(vector<char> unsorted)
{
    vector<char> ans(unsorted);
    int size = unsorted.size();
    if(size == 0)
        return ans;
    int front = 0;
    swap(ans, front, size - 1, 'R');
    swap(ans, front, size - 1, 'G');
    return ans;
}

void rand_populate(vector<char> &unsorted, int n)
{
    char c;
    while(n--)
    {
        c = rand() % 3;
        unsorted.push_back(c == 0 ? 'R' : c == 1 ? 'G' : 'B');
    }
}

int main()
{
    srand(time(0));
    int n = 10;
    vector<char> unsorted;
    rand_populate(unsorted, n);
    for(auto x: unsorted)
        cout<<x;
    cout<<endl;
    vector<char> sorted = sort_array(unsorted);
    for(auto x: sorted)
        cout<<x;
    cout<<endl;
    return 0;
}
