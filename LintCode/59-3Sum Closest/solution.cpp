class Solution {
public:
    /**
     * @param numbers: Give an array numbers of n integer
     * @param target: An integer
     * @return: return the sum of the three integers, the sum closest target.
     */
    int threeSumClosest(vector<int> &numbers, int target) {
        // write your code here
        int n = numbers.size();
        sort(numbers.begin(), numbers.end());
        long long ans = INT_MAX;
        for(int i = 0; i < n - 2; i++)
        {
            int l = i + 1, r = n - 1;
            while(l < r)
            {
                long long sum = numbers[i] + numbers[l] + numbers[r];
                if(abs(sum - target) < abs(ans - target))
                    ans = sum;
                if(sum < target)
                    l++;
                else
                    r--;
            }
        }
        return ans;
    }
};
