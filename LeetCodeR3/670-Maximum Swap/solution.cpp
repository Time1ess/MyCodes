class Solution {
public:
    int maximumSwap(int num) {
        vector<int> last_position(10, -1);
        string num_str = to_string(num);
        for (int i = 0; i < num_str.length(); i++) {
            last_position[num_str[i] - '0'] = i;
        }
        for (int i = 0; i < num_str.length(); i++) {
            for (int j = 9; j > num_str[i] - '0'; j--) {
                if (last_position[j] > i) {
                    swap(num_str[i], num_str[last_position[j]]);
                    return stoi(num_str);
                }
            }
        }
        return num;
    }
};
