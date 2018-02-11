class Solution {
private:
    vector<int> indices;
    vector<int> nums;
    int size;
public:
    Solution(vector<int> nums) {
        this->nums = nums;
        size = nums.size();
        reset();
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        indices.clear();
        for(int i = 0; i < size; i++)
            indices.push_back(i);
        return nums;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        for(int i = 0; i < size; i++)
        {
            int k = rand() % (i + 1);
            swap(indices[i], indices[k]);
        }
        vector<int> ans;
        for(int i = 0; i < size; i++)
            ans.push_back(nums[indices[i]]);
        return ans;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */
