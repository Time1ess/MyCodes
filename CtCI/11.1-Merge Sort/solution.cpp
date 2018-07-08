#include <vector>
#include <iostream>

using namespace std;


class Solution {
public:
  void merge(vector<int>& a, int n, vector<int>& b, int m) {
    int x = n - 1;
    int y = m - 1;
    int z = n + m - 1;
    while (x >= 0 || y >= 0) {
      int t;
      if (x >= 0 && y >= 0) {
        if (a[x] >= b[y]) {
          t = a[x--];
        } else {
          t = b[y--];
        }
      } else if (x >= 0) {
        t = a[x--];
      } else {
        t = b[y--];
      }
      a[z--] = t;
    }
  }
};


int main() {
  vector<int> a = {1,3,4,5,6,7};
  vector<int> b = {2,3,5,6,9};
  int n = a.size();
  int m = b.size();
  for(auto x: a)
    cout<<x<<endl;
  cout<<"----"<<endl;
  for(auto x: b)
    cout<<x<<endl;
  cout<<"----"<<endl;
  a.resize(n + m);
  Solution sol;
  sol.merge(a, n, b, m);
  for(auto x: a)
    cout<<x<<endl;
  return 0;
}
