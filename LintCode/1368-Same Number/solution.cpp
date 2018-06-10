class Solution {
public:
    /**
     * @param nums: the arrays
     * @param k: the distance of the same number
     * @return: the ans of this question
     */
    string sameNumber(vector<int> &nums, int k) {
        unordered_map<int, int> indices;
        unordered_map<int, bool> satisfieds;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (indices.find(nums[i]) != indices.end()) {
                int dist = i - indices[nums[i]];
                satisfieds[nums[i]] = satisfieds[nums[i]] || dist < k;
            } else {
                satisfieds[nums[i]] = false;
            }
            indices[nums[i]] = i;
        }
        bool anySatisfied = false;
        for (auto x: satisfieds) {
            anySatisfied = anySatisfied || x.second;
        }
        return anySatisfied ? "YES" : "NO";
    }
};
