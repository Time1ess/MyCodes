class Solution {
public:
    int bsearch(vector<int> &numbers, int s, int e, int t)
    {
        if(s >= e)
            return e;
        int m = s + (e - s) / 2;
        if(numbers[m] == t)
            return m;
        else if(numbers[m] > t)
            return bsearch(numbers, s, m - 1, t);
        else
            return bsearch(numbers, m + 1, e, t);
    }
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> ans;
        int n = numbers.size();
        for(int index1 = 0; index1 < n - 1; index1++)
        {
            int index2 = bsearch(numbers, index1 + 1, n - 1, target - numbers[index1]);
            if(numbers[index1] + numbers[index2] == target)
            {
                ans.push_back(index1+1);
                ans.push_back(index2+1);
                break;
            }
        }
        return ans;
    }
};
