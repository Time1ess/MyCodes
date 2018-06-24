class CloseNumber {
public:
    int getNext(int x) {
        int t = x;
        int c0 = 0;
        while((t & 0b1) == 0 && t != 0) {
            c0++;
            t >>= 1;
        }
        int c1 = 0;
        while((t & 0b1) == 1) {
            c1++;
            t >>= 1;
        }
        if(c0 + c1 >= 31 || c0 + c1 == 0) {
            return -1;
        }
        int p = c0 + c1;  // Last non-trailing zero
        x |= (1 << p);  // Flip last non-trailing zero
        x &= ~((1 << p) - 1);  // Set all bits after last non-trailing zero to zero
        x |= (1 << (c1 - 1)) - 1;  // Sort bits asc
        return x;
    }
    int getPrev(int x) {
        int t = x;
        int c1 = 0;
        while((t & 0b1) == 1) {
            c1++;
            t >>= 1;
        }
        if(t == 0)  // Wrong Format: 00000111111
            return -1;
        int c0 = 0;
        while((t & 0b1) == 0 && t != 0) {
            c0++;
            t >>= 1;
        }
        int p = c0 + c1;
        x &= ~((1 << (p+1)) - 1);  // Set all bits beginning from last non-trailing one to zero
        x |= ((1 << (c1+1)) - 1) << (c0 - 1);  // Sort bits desc
        return x;
    }
    vector<int> getCloseNumber(int x) {
        return {getPrev(x), getNext(x)};
    }
};
