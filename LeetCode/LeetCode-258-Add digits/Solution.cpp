class Solution {
public:
    int addDigits(int num) {
        if(num<10)
        return num;
        else
        return num-9*(int((num-1)/9));
    }
};
