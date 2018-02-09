class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int m = image.size();
        int n = image[0].size();
        set<pair<int, int>> visited;
        queue<pair<int, int>> nexts;
        const static vector<pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        nexts.push({sr, sc});
        int srcColor = image[sr][sc];
        while(!nexts.empty())
        {
            pair<int, int> p = nexts.front();
            nexts.pop();
            image[p.first][p.second] = newColor;
            visited.insert(p);
            for(auto d: directions)
            {
                pair<int, int> np = make_pair(p.first + d.first, p.second + d.second);
                if(np.first < 0 || np.first >= m || np.second < 0 || np.second >= n)
                    continue;
                if(visited.find(np) != visited.end() || image[np.first][np.second] != srcColor)
                    continue;
                nexts.push(np);
            }
        }
        return image;
    }
};
