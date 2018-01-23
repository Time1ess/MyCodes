#include <iostream>
#include <vector>

using namespace std;


class Solution
{
public:
    string shortest_balance_parentheses(int N)
    {
        if(N == 0)
            return "";
        int base = 1;
        while(base * base <= N)
            base++;
        base--;
        int div = N / base;
        int mod = N % base;
        string ans = "";
        for(int i = 1; i <= base; i++)
        {
            ans.push_back('(');
            if(i == mod)
                ans.push_back(')');
        }
        for(int i = 1; i <= div; i++)
            ans.push_back(')');
        return ans;
    }
};


int main()
{
    Solution sol;
    for(int i = 0; i < 50; i++)
    {
        cout<<"i = "<<i<<endl;
        cout<<sol.shortest_balance_parentheses(i)<<endl;
    }
    return 0;
}
