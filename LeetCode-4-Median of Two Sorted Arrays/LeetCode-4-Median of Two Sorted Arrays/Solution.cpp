#define min(a,b) ((a)<(b))?(a):(b)
class Solution {
public:
	double findMedianSortedArrays(int A[], int m, int B[], int n) {
		int l = (m + n + 1) >> 1;//when m+n is even,l+1=r
		int r = (m + n + 2) >> 1;//when m+n is odd, l=r
		return (getkth(A, m, B, n, l) + getkth(A, m, B, n, r)) / 2.0;
	}
	int getkth(int A[], int m, int B[], int n, int k){
		//getkth(array A,A.size,array B,B.size,Kth to find)
		//k is about the half of (m+n)

		//make sure that m<=n
		if (m > n)
			return getkth(B, n, A, m, k);

		if (m == 0)
			return B[k - 1];

		if (k == 1)
			return min(A[0], B[0]);

		int i = min(m, k / 2); //
		int j = k / 2;//

		if (A[i - 1] > B[j - 1])
			return getkth(A, m, B + j, n - j, k - j);
		else
			return getkth(A + i, m - i, B, n, k - i);
	}
};
#include <iostream>
using namespace std;

int main()
{
	int A[5] = { 1, 2, 3, 4, 5 };
	int B[6] = { 3, 6, 7, 10, 11, 15 };
	Solution s;
	cout << s.findMedianSortedArrays(A, 5, B, 6);
	cin.get();
}