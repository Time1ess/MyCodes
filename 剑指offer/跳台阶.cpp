class Solution {
public:
    int jumpFloor(int number) {
        if(number <= 1)
            return number;
		int fm2 = 1, fm1 = 1, f;
        for(int i = 2; i <= number; i++)
        {
            f = fm1 + fm2;
            fm2 = fm1;
            fm1 = f;
        }
        return f;
    }
};
