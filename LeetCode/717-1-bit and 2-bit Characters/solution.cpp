class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int i = 0, size = bits.size();
        while(i < size - 1)
        {
            if(bits[i] == 1)
                i += 2;
            else
                i += 1;
        }
        if(i == size - 1 && bits[i] == 0)
            return true;
        else
            return false;
    }
};
