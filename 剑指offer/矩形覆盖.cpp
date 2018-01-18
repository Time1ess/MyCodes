class Solution {
public:
    int rectCover(int number) {
		if(number <= 1)
            return number;
        int fm2 = 1, fm1 = 1, f;
        for(int i = 2; i <= number; i++)
        {
            f = fm2 + fm1;
            fm2 = fm1;
            fm1 = f;
        }
        return f;
    }
};
