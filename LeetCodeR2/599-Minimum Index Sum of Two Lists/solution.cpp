class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> rest_indices;
        int n = list1.size(), m = list2.size();
        int min_sum = INT_MAX;
        vector<string> ans;
        for(int i = 0; i < n; i++)
            rest_indices[list1[i]] = i;
        for(int j = 0; j < m; j++)
        {
            auto it = rest_indices.find(list2[j]);
            if(it == rest_indices.end())
                continue;
            int sum = it->second + j;
            if(sum == min_sum)
                ans.push_back(list2[j]);
            else if(sum < min_sum)
            {
                min_sum = sum;
                ans.clear();
                ans.push_back(list2[j]);
            }
        }
        return ans;
    }
};
