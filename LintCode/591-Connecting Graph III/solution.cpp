class ConnectingGraph3 {
private:
    unordered_map<int, int> parents;
    int n;
public:
    /*
    * @param n: An integer
    */ConnectingGraph3(int n) {
        // do intialization if necessary
        this->n = n;
        for(int i = 1; i <= n; i++)
            parents[i] = i;
    }
    
    int find(int x)
    {
        if(parents[x] != x)
            parents[x] = find(parents[x]);
        return parents[x];
    }
    /*
     * @param a: An integer
     * @param b: An integer
     * @return: nothing
     */
    void connect(int a, int b) {
        // write your code here
        int pa = find(a), pb = find(b);
        if(pa == pb)
            return;
        n--;
        parents[pa] = pb;
    }

    /*
     * @return: An integer
     */
    int query() {
        return n;
    }
};
