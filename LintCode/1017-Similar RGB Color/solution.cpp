class Solution {
public:
    /**
     * @param color: the given color
     * @return: a 7 character color that is most similar to the given color
     */
    int hexToInt(char ch) {
        if (ch >= '0' && ch <= '9') {
            return ch - '0';
        }
        return ch - 'a' + 10;
    }
    char intToHex(int x) {
        if (x >= 0 && x <= 9) {
            return x + '0';
        }
        return x + 'a' - 10;
    }
    vector<int> extract_rgb(const string &color) {
        vector<int> res;
        int n = color.length();
        if (n == 4) {
            // Short, #ABC
            for (int i = 1; i < n; i++) {
                res.push_back(hexToInt(color[i]) * 17);
            }
        } else {
            // Full, #ABCDEF
            for (int i = 1; i < n; i+=2) {
                res.push_back(hexToInt(color[i]) * 16 + hexToInt(color[i+1]));
            }
        }
        return res;
    }
    string buildRGBString(const vector<int>& rgb) {
        string res = "#";
        for (auto x: rgb) {
            res.push_back(intToHex(x));
            res.push_back(intToHex(x));
        }
        return res;
    }
    string similarRGB(string &color) {
        // Write your code here
        vector<int> rgb = extract_rgb(color);
        vector<int> simRGB;
        for (auto x: rgb) {
            simRGB.push_back((int)round(x / 17.0));
        }
        return buildRGBString(simRGB);
    }
};
