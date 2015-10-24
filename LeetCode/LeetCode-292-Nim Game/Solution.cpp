class Solution {
public:
    bool canWinNim(int n) {
        int left=n%4;
        if(left>=1&&left<=3)
        return true;
        else
        return false;
    }
};
