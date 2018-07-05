class Solution {
public:
    /**
     * @param n: an integer 
     * @return: the number of '1's in the first N number in the magical string S
     */
    int magicalString(int n) {
        // write your code here
        if(n <= 3)
            return 1;
        queue<int> q;
        bool is_one = false;
        q.push(1);
        q.push(1);
        int cnt = 0;
        int cnt_ones = 1;
        for(int i = 4; i <= n; i++) {
            int x = q.front();
            q.pop();
            if(x == 1)
                cnt_ones++;
            for(int k = 0; k < x; k++)
                if(is_one)
                    q.push(1);
                else
                    q.push(2);
            is_one = !is_one;
        }
        return cnt_ones;
    }
};
