#include <iostream>
#include <vector>

using namespace std;


void print_numbers(vector<char> &numbers)
{
    bool leading_zero = true;
    for(int i = 0; i < numbers.size(); i++)
        if(numbers[i] != '0' || !leading_zero)
        {
            cout<<numbers[i];
            leading_zero = false;
        }
    if(!leading_zero)
        cout<<endl;
}

void increment_print_recursively(vector<char> &numbers, int index)
{
    int size = numbers.size();
    if(index == size)
    {
        print_numbers(numbers);
        return;
    }
    for(int i = 0; i <= 9; i++)
    {
        numbers[index] = '0' + i;
        increment_print_recursively(numbers, index + 1);
    }
}


void print_from_1_to_max_N_digits(int n)
{
    if(n <= 0)
        return;
    vector<char> numbers(n, 0);
    increment_print_recursively(numbers, 0);
}


int main()
{
    print_from_1_to_max_N_digits(2);
    return 0;
}
