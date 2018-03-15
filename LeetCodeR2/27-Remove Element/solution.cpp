class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int i = 0;
        int j = 0;
        while(i < n)
        {
            if(nums[i] == val)
            {
                i++;
                continue;
            }
            
            if(i != j)
            {
                nums[j++] = nums[i];
                nums[i] = val;
            }
            else
                j++;
            i++;
        }
        return j;
    }
};
