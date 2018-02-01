class Solution {
public:
    /*
     * @param n: An integer
     * @param edges: a list of undirected edges
     * @return: true if it's a valid tree, or false
     */
    int find(vector<int> &rels, int x)
    {
        if(rels[x] != x)
            rels[x] = find(rels, rels[x]);
        return rels[x];
    }
    void merge(vector<int> &rels, int x1, int x2, int p1, int p2)
    {
        rels[p1] = p2;
    }
    bool validTree(int n, vector<vector<int>> &edges) {
        // write your code here
        int size = edges.size();
        if(n == 1)
            return true;
        if(size == 0)
            return false;
        vector<int> rels;
        for(int i = 0; i < n; i++)
            rels.push_back(i);
        for(auto edge: edges)
        {
            int x1 = edge[0];
            int x2 = edge[1];
            int p1 = find(rels, x1);
            int p2 = find(rels, x2);
            cout<<p1<<" "<<p2<<endl;
            if(p1 != p2)
                merge(rels, x1, x2, p1, p2);
            else
                return false;
        }
        int p;
        for(int i = 0; i < n; i++)
        {
            if(i == 0)
                p = find(rels, i);
            else if(find(rels, i) != p)
                return false;
        }
        return true;
    }
};
