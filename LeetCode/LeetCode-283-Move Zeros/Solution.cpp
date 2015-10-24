class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int non_pos=-1;
        int tmp;
        int size=nums.size();
        for(int i=0;i<size;)
        {
            if(nums[i]!=0)
            {
                i++;
                continue;                
            }
            non_pos=i+1;
            while(non_pos<size&&nums[non_pos]==0)
            non_pos++;
            if(non_pos==size)
            break;
            nums[i]=nums[non_pos];
            nums[non_pos]=0;
            i++;
        }
    }
};
