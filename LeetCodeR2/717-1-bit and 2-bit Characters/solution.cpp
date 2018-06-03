class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        bool two_bit = false;
        int n = bits.size();
        for (int i = 0; i < n - 1; i++) {
            if (two_bit) {
                two_bit = false;
            } else if (bits[i] == 1) {
                two_bit = true;
            }
        }
        return !two_bit;
    }
};
