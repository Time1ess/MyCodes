class Solution {
public:
     int  NumberOf1(int n) {
         int cnt = 0;
         while(n)
         {
             cnt ++;
             n = n & (n - 1);
         }
         return cnt;
     }
};
