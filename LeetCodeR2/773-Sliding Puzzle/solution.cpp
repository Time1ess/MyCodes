class Solution {
public:
    bool finished(const vector<vector<int>> &board)
    {
        int i = 1;
        if(board[1][2] != 0)
            return false;
        for(;i < 6; i++)
            if(board[i/4][(i-1)%3] != i)
                return false;
        return true;
    }
    int slidingPuzzle(vector<vector<int>>& board) {
        const vector<pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        queue<pair<vector<vector<int>>, int>> q;
        set<vector<vector<int>>> visited;
        q.push({board, 0});
        while(!q.empty())
        {
            pair<vector<vector<int>>, int> t = q.front();
            q.pop();
            if(finished(t.first))
                return t.second;
            visited.insert(t.first);
            int i = 0, j = 0;
            bool found = false;
            for(; i < 2; i++)
            {
                for(j = 0; j < 3; j++)
                    if(t.first[i][j] == 0)
                    {
                        found = true;
                        break;
                    }
                if(found)
                    break;
            }
            for(auto d: directions)
            {
                int ti = i + d.second;
                int tj = j + d.first;
                if(ti < 0 || ti == 2 || tj < 0 || tj == 3)
                    continue;
                vector<vector<int>> new_board = t.first;
                swap(new_board[i][j], new_board[ti][tj]);
                if(visited.find(new_board) != visited.end())
                    continue;
                q.push({new_board, t.second + 1});
            }
        }
        return -1;
    }
};
