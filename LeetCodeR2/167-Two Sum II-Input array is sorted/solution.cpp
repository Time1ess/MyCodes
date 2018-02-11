class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> ans;
        int n = numbers.size();
        int index1 = 0, index2 = n - 1;
        while(index1 < index2)
        {
            int t = numbers[index1] + numbers[index2];
            if(t == target)
            {
                ans.push_back(index1+1);
                ans.push_back(index2+1);
                break;
            }
            else if(t > target)
                index2--;
            else
                index1++;
        }
        return ans;
    }
};
