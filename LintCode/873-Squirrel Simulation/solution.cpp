class Solution {
public:
    /**
     * @param height: the height
     * @param width: the width
     * @param tree: the position of tree
     * @param squirrel: the position of squirrel
     * @param nuts: the position of nuts
     * @return: the minimal distance 
     */
    int distance(vector<int> &p1, vector<int> &p2)
    {
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
    }
    int minDistance(int height, int width, vector<int> &tree, vector<int> &squirrel, vector<vector<int>> &nuts) {
        // Write your code here
        int tmp = 0;
        for(auto nut: nuts)
            tmp += 2 * distance(nut, tree);
        int ans = INT_MAX;
        for(auto nut: nuts)
        {
            int new_ans = tmp - distance(tree, nut) + distance(squirrel, nut);
            if(new_ans < ans)
                ans = new_ans;
        }
        return ans;
    }
};
