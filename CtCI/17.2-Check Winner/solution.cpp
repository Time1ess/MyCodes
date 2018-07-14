class Board {
public:
    bool checkWon(vector<vector<int> > board) {
        // Check Row
        int n = board.size();
        for(int i = 0; i < n; i++) {
            if(board[i][0] == 1) {
                bool win = true;
                for(int j = 1; j < n; j++) {
                    if(board[i][j] != board[i][j-1]) {
                        win = false;
                        break;
                    }
                }
                if(win) {
                    return true;
                }
            }
        }
        // Check Columne
        for(int j = 0; j < n; j++) {
            if(board[0][j] == 1) {
                bool win = true;
                for(int i = 1; i < n; i++) {
                    if(board[i][j] != board[i-1][j]) {
                        win = false;
                        break;
                    }
                }
                if(win) {
                    return true;
                }
            }
        }
        // Check Diagonal
        if(board[0][0] == 1) {
            for(int i = 1; i < n; i++) {
                if(board[i][i] != board[i-1][i-1]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};
