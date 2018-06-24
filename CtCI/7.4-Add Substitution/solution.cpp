class AddSubstitution {
public:
    int negative(int x) {
        int neg = 0;
        int delta = x > 0 ? -1 : 1;
        while(x != 0) {
            neg += delta;
            x += delta;
        }
        return neg;
    }
    int calc(int a, int b, int type) {
        // write code here
        if(type == 1) { // Product
            if(b == 1)
                return a;
            return a + calc(a, calc(b, 1, -1), 1);  // a + a * (b - 1)
        } else if(type == 0) {  // Divide
            if(a < b)
                return 0;
            return 1 + calc(calc(a, b, -1), b, 0);  // 1 + (a - b) / b;
        } else {  // Minus
            return a + negative(b);
        }
    }
};
