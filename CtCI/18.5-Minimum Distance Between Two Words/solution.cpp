class Distance {
public:
    int getDistance(vector<string> article, int n, string x, string y) {
        // write code here
        int min_dist = INT_MAX;
        int last_idx_x = -1, last_idx_y = -1;
        for(int i = 0; i < n; i++) {
            const string& word = article[i];
            if(word == x) {
                last_idx_x = i;
            } else if(word == y) {
                last_idx_y = i;
            }
            if(last_idx_x != -1 && last_idx_y != -1) {
                min_dist = min(min_dist, abs(last_idx_x - last_idx_y));
            }
        }
        return min_dist;
    }
};
