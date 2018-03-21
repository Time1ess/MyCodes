class Solution {
public:
    /**
     * @param board: the given board
     * @return:  the least number of moves required so that the state of the board is solved
     */
    int hash_board(vector<vector<int>> &board)
    {
        int hash = 0;
        for(auto row: board)
            for(auto num: row)
                hash = hash * 10 + (num == 0 ? 9 : num);
        return hash;
    }
    bool solved(vector<vector<int>> &board)
    {
        static const vector<vector<int>> solved_board{{1,2,3},{4,5,0}};
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 3; j++)
                if(solved_board[i][j] != board[i][j])
                    return false;
        return true;
    }
    int slidingPuzzle(vector<vector<int>> &board) {
        // write your code here
        queue<pair<vector<vector<int>>, int>> q;
        unordered_set<int> visited;
        q.push({board, 0});
        visited.insert(hash_board(board));
        static const vector<pair<int, int>> directions{
            {0, -1}, {0, 1}, {1, 0}, {-1, 0}};
        while(!q.empty())
        {
            auto front = q.front();
            q.pop();
            vector<vector<int>> current = front.first;
            if(solved(current))
                return front.second;
            int zi = 0, zj = 0;
            for(int i = 0; i < 2; i++)
                for(int j = 0; j < 3; j++)
                    if(current[i][j] == 0)
                    {
                        zi = i;
                        zj = j;
                        break;
                    }
            for(auto d: directions)
            {
                int ni = zi + d.first;
                int nj = zj + d.second;
                if(ni >= 0 && ni < 2 && nj >= 0 && nj < 3)
                    {
                        swap(current[zi][zj], current[ni][nj]);
                        int hash = hash_board(current);
                        if(visited.find(hash) == visited.end())
                        {
                            q.push({current, front.second+1});
                            visited.insert(hash);
                        }
                        swap(current[zi][zj], current[ni][nj]);
                    }
            }
        }
        return -1;
    }
};
