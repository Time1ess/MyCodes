class CrossLine {
public:
    bool checkCrossLine(double s1, double s2, double y1, double y2) {
        // write code here
        return abs(s1 - s2) > 1e-6 || (abs(s1 - s2) <= 1e-6 && abs(y1 - y2) <= 1e-6);
    }
};
