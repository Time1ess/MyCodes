#include <iostream>
#include <vector>

using namespace std;


void print(vector<int> & numbers)
{
    bool leading = true;
    for(unsigned int i = 1; i < numbers.size(); i++)
        if(numbers[i] != 0 || !leading)
        {
            leading = false;
            cout<<numbers[i];
        }
    cout<<endl;
}


bool increment(vector<int> &numbers)
{
    int size = numbers.size();
    numbers[size - 1]++;
    int i = size - 1;
    while(i >= 1)
    {
        if(numbers[i] == 10)
        {
            numbers[i] = 0;
            numbers[i-1]++;
        }
        i--;
    }
    return numbers[0] != 1;  // is overflow?
}


void print_from_1_to_max_N_digits(int n)
{
    vector<int> numbers(n + 1, 0);
    while(increment(numbers))
        print(numbers);
}


int main()
{
    print_from_1_to_max_N_digits(3);
    return 0;
}
