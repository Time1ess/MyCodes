class BinInsert {
public:
    int binInsert(int n, int m, int j, int i) {
        // write code here
        // i >= j
        // 1. Get a mask like 111000111
        // Get 111000000
        int mask = ~((1 << (i + 1)) - 1);
        // Get 111000111
        mask |= ((1 << (j + 1)) - 1);
        // 2. Clear n with mask
        n &= mask;
        // 3. Left move m
        // 4. Set moved m to n
         n |= (m << j);
        return n;
    }
};
