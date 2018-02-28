
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
        int top = disks.top();
        disks.pop();
        t.add(top);
    }

    /*
     * @param n: An integer
     * @param destination: a tower
     * @param buffer: a tower
     * @return: nothing
     */
    void moveDisks(int n, Tower &destination, Tower &buffer) {
        // Move n Disks from this tower to destination by buffer tower
        if(n > 0)
        {
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

/**
 * Your Tower object will be instantiated and called as such:
 * vector<Tower> towers;
 * for (int i = 0; i < 3; i++) towers.push_back(Tower(i));
 * for (int i = n - 1; i >= 0; i--) towers[0].add(i);
 * towers[0].moveDisks(n, towers[2], towers[1]);
 * print towers[0], towers[1], towers[2]
*/
