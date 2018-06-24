class KthNumber {
public:
    int findKth(int k) {
        // write code here
        vector<int> nums = {3, 5, 7};
        int p3 = 0, p5 = 0, p7 = 0;
        for(int i = 4; i <= k; i++) {
            int n3 = 3 * nums[p3];
            int n5 = 5 * nums[p5];
            int n7 = 7 * nums[p7];
            int mmin = min(n3, min(n5, n7));
            nums.push_back(mmin);
            while(3 * nums[p3] <= mmin)
                p3++;
            while(5 * nums[p5] <= mmin)
                p5++;
            while(7 * nums[p7] <= mmin)
                p7++;
        }
        return nums[k-1];
    }
};
