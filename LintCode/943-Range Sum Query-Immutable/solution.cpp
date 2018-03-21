class NumArray {
private:
    vector<int> pre_sum;
public:
    /**
     * @return: nothing
     */
    NumArray(vector<int> nums){
        int sum = 0;
        for(int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            pre_sum.push_back(sum);
        }
    }
    
    int sumRange(int i, int j) {
        if(i == 0)
            return pre_sum[j];
        else
            return pre_sum[j] - pre_sum[i-1];
    }
};
