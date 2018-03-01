/**
 * Definition for a Connection.
 * class Connection {
 * public:
 *   string city1, city2;
 *   int cost;
 *   Connection(string& city1, string& city2, int cost) {
 *       this->city1 = city1;
 *       this->city2 = city2;
 *       this->cost = cost;
 * }
 */

bool cmp(const Connection &a, const Connection &b)
{
    return a.cost < b.cost || (a.cost == b.cost && a.city1 < b.city1)
        || (a.cost == b.cost && a.city1 == b.city1 && a.city2 < b.city2);
}

class Solution {
public:
    /**
     * @param connections given a list of connections include two cities and cost
     * @return a list of connections from results
     */
     
    string find(unordered_map<string, string> &parents, string x)
    {
        if(x != parents[x])
            parents[x] = find(parents, parents[x]);
        return parents[x];
    }
     
    vector<Connection> lowestCost(vector<Connection>& connections) {
        // Write your code here
        vector<Connection> ans;
        int n = connections.size();
        if(n == 0)
            return ans;
        sort(connections.begin(), connections.end(), cmp);
        unordered_map<string, string> parents;
        for(auto c: connections)
        {
            parents[c.city1] = c.city1;
            parents[c.city2] = c.city2;
        }
        for(auto c: connections)
        {
            string p_src = find(parents, c.city1);
            string p_dst = find(parents, c.city2);
            if(p_src == p_dst)
                continue;
            parents[p_dst] = p_src;
            ans.push_back(c);
        }
        string root = find(parents, connections[0].city1);
        for(auto c: connections)
            if(root != find(parents, c.city1) || root != find(parents, c.city2))
            {
                ans.clear();
                break;
            }
        return ans;
    }
};
