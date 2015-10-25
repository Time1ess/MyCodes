//Solution 2
//class Solution {
//public:
//    int missingNumber(vector<int>& nums) {
//        int ans=nums.size();
//        for(int i=0;i<nums.size();i++)
//        {
//            ans^=(i^nums[i]);
//        }
//        return ans;
//    }
//};

//Solution 1
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int ans=0;
        for(int i=0;i<nums.size();i++)
        {
            ans^=((i+1)^nums[i]);
        }
        return ans;
    }
};
