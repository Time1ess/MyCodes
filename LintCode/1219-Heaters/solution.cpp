class Solution {
public:
    /**
     * @param houses: positions of houses
     * @param heaters: positions of heaters
     * @return: the minimum radius standard of heaters
     */
    int findRadius(vector<int> &houses, vector<int> &heaters) {
        // Write your code here
        int n = houses.size();
        int m = heaters.size();
        if (n == 0 || m == 0)
            return 0;
        int min_rad = 0;
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int j = 0;
        for (int i = 0; i < n; i++) {
            int dist = abs(houses[i] - heaters[j]);
            while (j < m - 1 && abs(houses[i] - heaters[j+1]) < dist) {
                dist = abs(houses[i] - heaters[j+1]);
                j++;
            }
            min_rad = max(min_rad, dist);
        }
        return min_rad;
    }
};
