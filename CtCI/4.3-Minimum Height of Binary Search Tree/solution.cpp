class MinimalBST {
public:
    int buildMinimalBSTHeight(int s, int e) {
        if(s == e)
            return 0;
        else if(s + 1 == e)
            return 1;
        int m = s + (e - s) / 2;
        return 1 + max(buildMinimalBSTHeight(s, m), buildMinimalBSTHeight(m + 1, e));
    }
    int buildMinimalBST(vector<int> vals) {
        // write code here
        int n = vals.size();
        return buildMinimalBSTHeight(0, n);
    }
};
