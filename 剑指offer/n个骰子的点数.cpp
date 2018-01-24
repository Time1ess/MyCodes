#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;


class Solution
{
public:
    void PrintProbability(int number, int max_value=6)
    {
        if(number < 1)
            return;
        int **cnts = new int*[2];
        for(int i = 0; i < 2; i++)
        {
            cnts[i] = new int[number * max_value + 1];
            for(int j = 0; j < number * max_value + 1; j++)
                cnts[i][j] = 0;
        }
        for(int j = 1; j <= max_value; j++)
            cnts[1][j] = 1;
        int flag = 0;
        for(int n = 2; n <= number; n++)
        {
            for(int k = 0; k < n; k++)  // At least n
                cnts[flag][k] = 0;
            for(int k = n; k < number * max_value + 1; k++)
            {
                cnts[flag][k] = 0;
                for(int j = 1; j <= k && j <= max_value; j++)
                    cnts[flag][k] += cnts[1 - flag][k-j];
            }
            flag = !flag;
        }
        double total = pow(max_value, number);
        for(int i = number; i < number * max_value + 1; i++)
            printf("%d: %.3f\n", i, (double)cnts[1 - flag][i] / total);
        delete[] cnts[1];
        delete[] cnts[0];
        delete[] cnts;
    }
};


int main()
{
    Solution sol;
    sol.PrintProbability(1);
    return 0;
}
