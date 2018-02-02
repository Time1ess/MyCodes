class Solution {
public:
    /*
     * @param numbers: Give an array numbers of n integer
     * @return: Find all unique triplets in the array which gives the sum of zero.
     */
    vector<vector<int>> threeSum(vector<int> &numbers) {
        // write your code here
        vector<vector<int>> ans;
        int size = numbers.size();
        if(size == 0)
            return ans;
        vector<int> _ans;
        sort(numbers.begin(), numbers.end());
        for(int i = 0; i < size - 1; i++)
        {
            int t = -numbers[i];
            int l = i + 1;
            int r = size - 1;
            while(l < r)
            {
                int s = numbers[l] + numbers[r];
                if(s > t)
                    r--;
                else if(s < t)
                    l++;
                else
                {
                    _ans.clear();
                    _ans.push_back(numbers[i]);
                    _ans.push_back(numbers[l]);
                    _ans.push_back(numbers[r]);
                    ans.push_back(_ans);
                    
                    l++;
                    r--;
                    while(l < r && numbers[l] == numbers[l-1])
                        l++;
                    while(l < r && numbers[r] == numbers[r+1])
                        r--;
                }
            }
            while(i < size - 1 && numbers[i] == numbers[i+1])
                i++;
        }
        return ans;
    }
};
