class Solution {
public:
    /**
     * @param arrs: the arrays
     * @return: the number of the intersection of the arrays
     */
    int intersectionOfArrays(vector<vector<int>> &arrs) {
        // write your code here
        int n = arrs.size();
        if(n == 0)
            return 0;
        for(int i = 0; i < n; i++)
            sort(arrs[i].begin(), arrs[i].end());
        vector<int> intersection = arrs[0];
        for(int i = 1; i < n; i++)
        {
            vector<int> new_intersection;
            for(auto x: intersection)
                if(binary_search(arrs[i].begin(), arrs[i].end(), x))
                    new_intersection.push_back(x);
            intersection = new_intersection;
            if(intersection.empty())
                break;
        }
        return intersection.size();
    }
};
