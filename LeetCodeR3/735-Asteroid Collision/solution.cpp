class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> ans;
        for (auto as : asteroids) {
            bool destroyed = false;
            while (!ans.empty() && ans.back() > 0 && as < 0) {
                if (abs(as) == ans.back()) {
                    destroyed = true;
                    ans.pop_back();
                    break;
                } else if (abs(as) < ans.back()) {
                    destroyed = true;
                    break;
                } else {
                    ans.pop_back();
                }
            }
            if (!destroyed) {
                ans.push_back(as);
            }
        }
        return ans;
    }
};
