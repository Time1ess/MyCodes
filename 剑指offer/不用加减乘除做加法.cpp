class Solution {
public:
    int Add(int num1, int num2)
    {
		int carry = 0;
        int sum = 0;
        do{
            sum = num1 ^ num2;
            carry = (num1 & num2) << 1;
            num1 = sum;
            num2 = carry;
        }while(num2);
        return num1;
    }
};
