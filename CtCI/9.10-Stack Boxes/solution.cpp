#include <unordered_map>

class Box {
public:
    bool can_place_above(vector<int>& w, vector<int>& l, vector<int>& h,
                         int idx, int bottom_idx) {
        return bottom_idx == -1 || (w[idx] < w[bottom_idx] && l[idx] < l[bottom_idx]);
    }
    int getHeight(unordered_map<int, int>& mem,
                  vector<int>& w, vector<int>& l, vector<int>& h, int bottom_idx, int n) {
        int max_height = 0;
        if(mem.find(bottom_idx) != mem.end())
            return mem[bottom_idx];
        for(int idx = 0; idx < n; idx++) {
            if(can_place_above(w, l, h, idx, bottom_idx)) {
                max_height = max(max_height, h[idx] + getHeight(mem, w, l, h, idx, n));
            }
        }
        mem[bottom_idx] = max_height;
        return max_height;
    }
    int getHeight(vector<int> w, vector<int> l, vector<int> h, int n) {
        // write code here
        unordered_map<int, int> mem;
        return getHeight(mem, w, l, h, -1, n);
    }
};
