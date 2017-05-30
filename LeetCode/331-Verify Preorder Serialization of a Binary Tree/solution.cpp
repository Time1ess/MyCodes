// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-10 09:02
// Last modified: 2017-05-10 09:02
// Filename: solution.cpp
// Description:
class Solution {
public:
    bool isValidSerialization(string preorder) {
        if(preorder.empty())
            return false;
        int degree = 1;
        for(int i = 0; i < preorder.length(); i++)
        {
            degree--;
            if(degree < 0)
                return false;
            if(preorder[i] != '#')
                degree += 2;
            while(i < preorder.length() && preorder[i] != ',')
                i++;
        }
        return degree == 0;
    }
};
