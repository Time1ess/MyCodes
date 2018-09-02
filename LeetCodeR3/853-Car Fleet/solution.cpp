class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        map<int, double> cost;
        int n = position.size();
        for (int i = 0; i < n; i++) {
            cost[-position[i]] = 1.0 * (target-position[i]) / speed[i];
        }
        int ans = 0;
        double cur = 0;
        for (auto p : cost) {
            if (p.second > cur) {
                cur = p.second;
                ans++;
            }
        }
        return ans;
    }
};
