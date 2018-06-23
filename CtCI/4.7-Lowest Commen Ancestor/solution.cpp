class LCA {
public:
    int getLCA(int a, int b) {
        // write code here
        return a == b ? a : getLCA(max(a, b) / 2, min(a, b));
    }
};
