class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        vector<int> ans;
        int size = array.size();
        if(size <= 1)
            return ans;
        int left = 0, right = size - 1;
        int best_mul = INT_MAX;
        while(left < right)
        {
            int lr_sum = array[left] + array[right];
            if(lr_sum == sum)
            {
                int current_mul = array[left] * array[right];
                if(current_mul < best_mul)
                {
                    best_mul = current_mul;
                    ans.clear();
                    ans.push_back(array[left]);
                    ans.push_back(array[right]);
                }
                left++;
                right--;
            }
            else if(lr_sum < sum)
                left++;
            else
                right--;
        }
        return ans;
    }
};
