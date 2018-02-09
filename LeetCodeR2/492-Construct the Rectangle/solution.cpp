class Solution {
public:
    vector<int> constructRectangle(int area) {
        for(int l = ceil(sqrt(area)); l <= area; l++)
        {
            if((area / l) * l == area)
            {
                vector<int> ans{l, area / l};
                return ans;
            }
        }
    }
};
