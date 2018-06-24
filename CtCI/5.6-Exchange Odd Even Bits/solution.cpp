class Exchange {
public:
    int exchangeOddEven(int x) {
        // write code here
        static const int evenMask = 0x55555555;
        static const int oddMask = 0xAAAAAAAA;
        return ((x & evenMask) << 1) | ((x & oddMask) >> 1);
    }
};
