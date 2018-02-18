class Solution {
public:
    int maxProduct(vector<string>& words) {
        if(words.size() <= 1)
            return 0;
        vector<pair<int, int>> len_bits;
        for(auto x: words)
        {
            int bits = 0;
            for(auto c: x)
                bits |= 1<<(c-'a');
            len_bits.push_back({x.length(), bits});
        }
        int maximum = 0;
        for(auto x: len_bits)
            for(auto y: len_bits)
                if((x.second & y.second) == 0)
                    maximum = max(maximum, x.first * y.first);
        return maximum;
    }
};
