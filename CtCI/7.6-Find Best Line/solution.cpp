/*
struct Point {
    int x;
    int y;
    Point() :
            x(0), y(0) {
    }
    Point(int xx, int yy) {
        x = xx;
        y = yy;
    }
};*/

#include <unordered_map>

class DenseLine {
private:
    double eps = 1e-4;
public:
    double Slope(const Point& p1, const Point& p2) {
        return 1.0 * (p1.y - p2.y) / (p1.x - p2.x);
    }
    double Intercept(const Point& p, double slope) {
        return p.y - p.x * slope;
    }
    double floor(double x) {
        int r = (int)(x / eps);
        return ((double) r) * eps;
    }
    int EquivalentLines(unordered_map<double, vector<double>>& lines, int s, int i) {
        double key = floor(s);
        return CountLines(lines[key], i) + CountLines(lines[key-eps], i) + CountLines(lines[key+eps], i);
    }
    int CountLines(vector<double>& intercepts, int i) {
        int cnt = 0;
        for(auto x: intercepts) {
            if(abs(x - i) <= eps)
                cnt++;
        }
        return cnt;
    }
    vector<double> getLine(vector<Point> p, int n) {
        // write code here
        vector<double> bestLine;
        int bestCount = 0;
        unordered_map<double, vector<double>> lines;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                const Point& p1 = p[i];
                const Point& p2 = p[j];
                if(p1.x == p2.x)
                    continue;
                double s = Slope(p1, p2);
                double i = Intercept(p1, s);
                lines[floor(s)].push_back(i);
                int count = EquivalentLines(lines, s, i);
                if(count > bestCount) {
                    bestLine = {s, i};
                    bestCount = count;
                }
            }
        }
        return bestLine;
    }
};
