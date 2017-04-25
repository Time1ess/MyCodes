// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-25 10:41
// Last modified: 2017-04-25 10:41
// Filename: solution.cpp
// Description:
#define MAX_STEP 6
class Solution {
public:
    string shrink(string s)
    {
        while(!s.empty())
        {
            int start = 0;
            bool done = true;
            for(int i =0; i <= s.size(); i++)
            {
                if(i == s.size() || s[i] != s[start])
                {
                    if(i - start >= 3)
                    {
                        s = s.substr(0, start) + s.substr(i);
                        done = false;
                        break;
                    }
                    start = i;
                }
            }
            if(done)
                break;
        }
        return s;
    }
    int DFS(string board, string hand)
    {
        if(board.empty())
            return 0;
        if(hand.empty())
            return MAX_STEP;
        int ans = MAX_STEP;
        for(int i = 0; i < hand.size(); i++)
        {
            int j = 0, n = board.size();
            while(j < n)
            {
                int k = board.find(hand[i], j);
                if(k == string::npos)
                    break;
                if(k < n - 1 && board[k] == board[k+1])
                {
                    // Two consecutive balls with same color on board
                    string next_board = shrink(board.substr(0, k) + board.substr(k+2));
                    if(next_board.empty())
                        return 1;
                    string next_hand = hand;
                    next_hand.erase(i, 1);
                    ans = min(ans, DFS(next_board, next_hand) + 1);
                    k++;
                }
                else if(i > 0 && hand[i] == hand[i-1])
                {
                    // Two consecutive balls with same color in hand
                    string next_board = shrink(board.substr(0, k) + board.substr(k+1));
                    if(next_board.empty())
                        return 2;
                    string next_hand = hand;
                    next_hand.erase(i-1, 2);
                    ans = min(ans, DFS(next_board, next_hand) + 2);
                }
                j = k + 1;
            }
        }
        return ans;
    }
    int findMinStep(string board, string hand) {
        sort(hand.begin(), hand.end());
        int ans = DFS(board, hand);
        return ans > hand.size() ? -1 : ans;
    }
};
