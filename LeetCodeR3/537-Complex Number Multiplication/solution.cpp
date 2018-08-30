class Solution {
public:
    pair<int, int> parseComplex(const string& a) {
        int n = a.length();
        int pos = a.find('+');
        int real = stoi(a.substr(0, pos));
        int vir = stoi(a.substr(pos+1, n - (pos + 1) - 1));
        return {real, vir};
    }
    string complexNumberMultiply(string a, string b) {
        auto pa = parseComplex(a);
        auto pb = parseComplex(b);
        int real = pa.first * pb.first - pa.second * pb.second;
        int vir = pa.first * pb.second + pa.second * pb.first;
        return to_string(real) + "+" + to_string(vir) + "i";
    }
};
