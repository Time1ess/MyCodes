class Solution {
public:
    /*
     * @param nums: An ineger array
     * @return: An integer
     */
    int removeDuplicates(vector<int> &nums) {
        // write your code here
        int n = nums.size();
        if(n == 0)
            return 0;
        int read = 1, write = 1;
        while(read < n)
        {
            int dup = nums[read-1];
            while(read < n && nums[read] == dup)
                read++;
            if(read == n)
                break;
            nums[write++] = nums[read++];
        }
        return write;
    }
};
