class MovingAverage {
private:
    queue<int> q;
    double sum;
    int size;
public:
    /*
    * @param size: An integer
    */MovingAverage(int size) {
        // do intialization if necessary
        this->size = size;
        this->sum = 0;
    }

    /*
     * @param val: An integer
     * @return:  
     */
    double next(int val) {
        if(size == 0)
            return 0;
        // write your code here
        if(int(q.size()) == size) {
            sum -= q.front();
            q.pop();
        }
        sum += val;
        q.push(val);
        return sum / int(q.size());
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param = obj.next(val);
 */
