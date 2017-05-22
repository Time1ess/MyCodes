// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-22 16:22
// Last modified: 2017-05-22 16:22
// Filename: solution.cpp
// Description:
class Solution {
public:
    string fractionAddition(string expression) {
        vector<pair<int, int>> v;
        int num, den, size = expression.size();
        bool neg = false, num_part = true;
        num = den = 0;
        for(int i = 0; i <= size; i++)
        {
            if(expression[i] == '+' || expression[i] == '-' || i == size)
            {
                if(i != 0)
                    v.push_back(make_pair(neg ? -num : num, den));
                if(i == size)
                    break;
                neg = expression[i] == '-';
                num = den = 0;
                num_part = true;
            }
            else if(expression[i] == '/')
                num_part = false;
            else
            {
                if(num_part)
                    num = num * 10 + expression[i] - '0';
                else
                    den = den * 10 + expression[i] - '0';
            }
        }
        int aden = 1;
        for(int i = 0; i < v.size(); i++)
        {
            if(v[i].second != 0 && aden % v[i].second != 0)
                aden *= v[i].second;
        }
        int anum = 0;
        for(int i = 0; i < v.size(); i++)
            anum += v[i].first * aden / v[i].second;
        if(anum == 0)
            return "0/1";
        for(int i = 9; i >= 2; i--)
            while(anum % i == 0 && aden % i == 0)
            {
                anum /= i;
                aden /= i;
            }
        return to_string(anum)+"/"+to_string(aden);
    }
};
