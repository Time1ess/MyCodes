class Exchange {
public:
    vector<int> exchangeAB(vector<int> AB) {
        // write code here
        AB[0] ^= AB[1];
        AB[1] ^= AB[0];
        AB[0] ^= AB[1];
        return AB;
    }
};
