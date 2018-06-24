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
class Bipartition {
public:
    vector<double> getBipartition(vector<Point> A, vector<Point> B) {
        // write code here
        Point p1((A[0].x + A[1].x + A[2].x + A[3].x) / 4.0,
                 (A[0].y + A[1].y + A[2].y + A[3].y) / 4.0);
        Point p2((B[0].x + B[1].x + B[2].x + B[3].x) / 4.0,
                 (B[0].y + B[1].y + B[2].y + B[3].y) / 4.0);
        double h = 1.0 * (p1.y - p2.y) / (p1.x - p2.x);
        double d = p1.y - h * p1.x;
        return {h, d};
    }
};
