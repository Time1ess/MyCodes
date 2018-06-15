class Solution {
public:
    /**
     * @param moves: a sequence of its moves
     * @return: if this robot makes a circle
     */
    bool judgeCircle(string &moves) {
        // Write your code here
        int ver = 0, hor = 0;
        for(auto c: moves) {
            if(c == 'R')
                hor++;
            else if(c == 'L')
                hor--;
            else if(c == 'U')
                ver++;
            else
                ver--;
        }
        return ver == 0 && hor == 0;
    }
};
