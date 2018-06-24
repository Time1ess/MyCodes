class Render {
public:
    vector<int> renderPixel(vector<int> screen, int x, int y) {
        // write code here
        for(int i = 0; i < screen.size(); i++) {
            for(int offset = 0; offset < 8; offset++) {
                int bitIdx = i * 8 + offset;
                if(bitIdx >= x && bitIdx <= y)
                    screen[i] |= 1 << offset;
            }
        }
        return screen;
    }
};
