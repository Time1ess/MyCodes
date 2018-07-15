#include <iostream>
#include <vector>
#include <cstdlib>
#include <unordered_map>

using namespace std;

class Solution {
public:
  vector<int> sampling(const vector<int>& nums, int m) {
    int n = nums.size();
    if(n <= m)
      return nums;
    
    vector<int> ans;
    int i = 0;
    while(i < n) {
      if(i < m) {
        ans.push_back(nums[i]);
      } else {
        int p = rand() % (i + 1);
        if(p < m) {
          ans[p] = nums[i];
        }
      }
      i++;
    }
    return ans;
  }
};

int main() {
  Solution sol;
  int m = 4;
  int repeated_times = 100000;
  int max_num = 10;
  vector<int> nums;
  for(int i = 0; i < max_num; i++) {
    nums.push_back(i);
  }
  unordered_map<int, int> cnts;
  int total_cnt = m * repeated_times;
  for(int r = 0; r < repeated_times; r++) {
    for(auto x: sol.sampling(nums, m)) {
      cnts[x]++;
    }
  }
  for(int x = 0; x < max_num; x++) {
    cout<<"Prob for [ " << x << " ]: " << 1.0 * cnts[x] / total_cnt << endl;
  }
  return 0;
}
