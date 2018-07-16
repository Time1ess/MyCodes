class Solution {
public:
    /**
     * @param ghosts: a 2D integer array
     * @param target: a integer array
     * @return: return boolean
     */
    int get_dist(vector<int>& a, vector<int>& b) {
        return abs(a[0] - b[0]) + abs(a[1] - b[1]);
    }
    bool escapeGhosts(vector<vector<int>> &ghosts, vector<int> &target) {
        // write your code here
        vector<int> mine = {0, 0};
        int mine_dist = get_dist(target, mine);
        for(auto ghost: ghosts) {
            if(get_dist(target, ghost) <= mine_dist) {
                return false;
            }
        }
        return true;
    }
};
