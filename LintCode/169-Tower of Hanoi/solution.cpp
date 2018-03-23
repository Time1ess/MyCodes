class Solution {
public:
    /**
     * @param n: the number of disks
     * @return: the order of moves
     */
    void Hanoi(vector<string> &ans, int n, string src, string through, string dst)
    {
        if(n == 1)
        {
            ans.push_back("from " + src + " to " + dst);
            return;
        }
        Hanoi(ans, n-1, src, dst, through);
        ans.push_back("from " + src + " to " + dst);
        Hanoi(ans, n-1, through, src, dst);
    }
    vector<string> towerOfHanoi(int n) {
        // write your code here
        vector<string> ans;
        Hanoi(ans, n, "A", "B", "C");
        return ans;
    }
};
