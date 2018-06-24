class Transform {
public:
    int getOneBitCnts(int x) {
        int cnt = 0;
        while(x) {
            cnt++;
            x &= x - 1;
        }
        return cnt;
    }
    int calcCost(int A, int B) {
        // write code here
        return getOneBitCnts(A ^ B);
    }
};
