class LoadBalancer {
private:
    unordered_map<int, int> locs;    
    vector<int> servers;
public:
    LoadBalancer() {
        // do intialization if necessary
    }

    /*
     * @param server_id: add a new server to the cluster
     * @return: nothing
     */
    void add(int server_id) {
        // write your code here
        locs[server_id] = servers.size();
        servers.push_back(server_id);
    }

    /*
     * @param server_id: server_id remove a bad server from the cluster
     * @return: nothing
     */
    void remove(int server_id) {
        // write your code here
        int loc = locs[server_id];
        int n = servers.size();
        swap(servers[n-1], servers[loc]);
        servers.pop_back();
        locs.erase(server_id);
        locs[servers[loc]] = loc;
    }

    /*
     * @return: pick a server in the cluster randomly with equal probability
     */
    int pick() {
        // write your code here
        return servers[random() % servers.size()];
    }
};
