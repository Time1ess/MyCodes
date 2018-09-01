class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int n = people.size();
        int ans = 0;
        int l = 0, r = n - 1;
        while (l <= r) {
            if (l == r) {
                ans++;
                break;
            }
            int tot = people[l] + people[r];
            ans++;
            if (tot <= limit) {
                l++;
            }
            r--;
        }
        return ans;
    }
};
