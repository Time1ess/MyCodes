static const vector<pair<int, int>> directions{
    {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};
class Solution {
public:
    bool fall(int N, int nx, int ny)
    {
        return nx < 0 || nx >= N || ny < 0 || ny >= N;
    }
    double alive_prob(int N, int x, int y)
    {
        int cnt = 0;
        for(auto d: directions)
        {
            int nx = x + d.first;
            int ny = y + d.second;
            if(fall(N, nx, ny))
                cnt++;
        }
        return 1.0 * (8 - cnt) / 8;
    }
    double knightProbability(int N, int K, int r, int c) {
        if(K == 0)
            return 1;
        vector<vector<double>> prob(N, vector<double>(N, 0));
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                prob[i][j] = alive_prob(N, i, j);
        for(int k = 2; k <= K; k++)
        {
            vector<vector<double>> new_prob(N, vector<double>(N, 0));
            for(int i = 0; i < N; i++)
                for(int j = 0; j < N; j++)
                    for(auto d: directions)
                    {
                        int nx = i + d.first;
                        int ny = j + d.second;
                        new_prob[i][j] += 1.0 / 8 * (fall(N, nx, ny) ? 0 : prob[nx][ny]);
                    }
            prob = new_prob;
        }
        return prob[r][c];
    }
};
