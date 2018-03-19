class Solution {
public:
    /**
     * @param N: The number of buses
     * @param route: The route of buses
     * @param A: Start bus station
     * @param B: End bus station
     * @return: Return the minimum transfer number
     */
    int getMinTransferNumber(int N, vector<vector<int>> &route, int A, int B) {
        // Write your code here
        queue<pair<int, int>> q;  // stop -- current_cost
        unordered_map<int, vector<int>> stops;
        unordered_set<int> visited;
        for(int bus_id = 0; bus_id < N; bus_id++)
            for(auto stop: route[bus_id])
                stops[stop].push_back(bus_id);
        q.push({A, 0});
        visited.insert(A);
        while(!q.empty())
        {
            auto front = q.front();
            q.pop();
            int stop = front.first;
            int cost = front.second;
            if(stop == B)
                return cost;
            for(auto bus: stops[stop])
                for(auto next_stop: route[bus])
                    if(visited.find(next_stop) == visited.end())
                    {
                        visited.insert(next_stop);
                        q.push({next_stop, cost + 1});
                    }
        }
        return -1;
    }
};
