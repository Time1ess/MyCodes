class Tower {
private:
    stack<int> disks;
public:
    /*
    * @param i: An integer from 0 to 2
    */
    Tower(int i) {
        // create three towers
    }

    /*
     * @param d: An integer
     * @return: nothing
     */
    void add(int d) {
        // Add a disk into this tower
        if (!disks.empty() && disks.top() <= d) {
            printf("Error placing disk %d", d);
        } else {
            disks.push(d);
        }
    }

    /*
     * @param t: a tower
     * @return: nothing
     */
    void moveTopTo(Tower &t) {
        // Move the top disk of this tower to the top of t.
        int x = disks.top();
        disks.pop();
        t.add(x);
    }

    /*
     * @param n: An integer
     * @param destination: a tower
     * @param buffer: a tower
     * @return: nothing
     */
    void moveDisks(int n, Tower &destination, Tower &buffer) {
        // Move n Disks from this tower to destination by buffer tower
        if(n == 1) {
            moveTopTo(destination);
        } else {
            moveDisks(n-1, buffer, destination);
            moveTopTo(destination);
            buffer.moveDisks(n-1, destination, *this);
        }
    }

    /*
     * @return: Disks
     */
    stack<int> getDisks() {
        // write your code here
        return disks;
    }
};
