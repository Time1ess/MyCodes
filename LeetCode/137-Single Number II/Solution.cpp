//Solution 1
//class Solution {
//public:
//    int singleNumber(vector<int>& nums) {
//        int cnts[32]={0};
//        int ans=0;
//        for(int i=0;i<32;i++)
//        {
//            for(int j=0;j<nums.size();j++)
//            {
//                cnts[i]+=((nums[j]>>i)&1);
//                cnts[i]%=3;
//            }
//            ans|=(cnts[i]<<i);
//        }
//        return ans;
//    }
//};
//Solution 2
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ones=0,twos=0;
        for(int i=0;i<nums.size();i++)
        {
            ones=(ones^nums[i])&~twos;
            twos=(twos^nums[i])&~ones;
        }
        return ones;
    }
};
