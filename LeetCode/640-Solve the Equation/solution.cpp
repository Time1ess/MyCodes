// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-10 10:47
// Last modified: 2017-07-10 10:47
// Filename: solution.cpp
// Description:
class Solution {
public:
    string solveEquation(string equation) {
        int equation_side = 0;
        int constant[2] = {0};
        int vars[2] = {0};
        int coef = 0;
        bool add = true, has_coef = false;
        equation = equation +"=";
        for(int i = 0; i < equation.length(); i++)
        {
            if(equation[i] >= '0' && equation[i] <= '9')
            {
                coef = coef * 10 + equation[i] - '0';
                has_coef = true;
            }
            else if(equation[i] == 'x')
            {
                vars[equation_side] += has_coef ? (add ? coef: -coef) : (add ? 1 : -1);
                coef = 0;
                has_coef = false;
            }
            else if(equation[i] == '=')
            {
                constant[equation_side] += add ? coef : -coef;
                equation_side = 1;
                coef = 0;
                has_coef = false;
                add = true;
            }
            else
            {
                constant[equation_side] += add ? coef : -coef;
                add = equation[i] == '+' ? true : false;
                coef = 0;
                has_coef = false;
            }
        }
        constant[1] -= constant[0];
        vars[0] -= vars[1];
        if(vars[0] == 0 && constant[1] == 0)
            return "Infinite solutions";
        else if(vars[0] == 0 && constant[1] != 0)
            return "No solution";
        else if(constant[1] == 0)
            return "x=0";
        else
            return "x="+to_string(constant[1] / vars[0]);
    }
};
