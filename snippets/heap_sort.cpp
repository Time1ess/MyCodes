#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_NUM 200


vector<int> generate_nums(int n) {
  vector<int> ans;
  for(int i = 0; i < n; i++) {
    ans.push_back(rand() % MAX_NUM);
  }
  return ans;
}

void heap_sort(vector<int>& nums) {
  int m = nums.size();
  while(m > 1) {
    for(int k = (m - 1) / 2; k >= 0; k--) {
      if(nums[k] < nums[2*k]) {
        swap(nums[k], nums[2*k]);
      }
      if(2 * k + 1 < m && nums[k] < nums[2*k+1]) {
        swap(nums[k], nums[2*k+1]);
      }
    }
    swap(nums[0], nums[m-1]);
    m--;
  }
}

bool vector_equal(const vector<int>& v1, const vector<int>& v2) {
  int n = v1.size();
  int m = v2.size();
  if(n != m) {
    return false;
  }
  for(int i = 0; i < n; i++) {
    if(v1[i] != v2[i]) {
      return false;
    }
  }
  return true;
}

void test_heap_sort(int n) {
  while(n--) {
    auto nums = generate_nums(rand() % 100);
    auto expected_nums = nums;
    sort(expected_nums.begin(), expected_nums.end());
    heap_sort(nums);
    if(!vector_equal(nums, expected_nums)) {
      cout<<"Test failed:"<<endl;
      for(auto x: nums) {
        cout<<x<<" ";
      }
      cout<<endl;
      for(auto x: expected_nums) {
        cout<<x<<" ";
      }
      cout<<endl;
    }
  }
}

int main() {
  srand(time(0));
  test_heap_sort(10000);
  return 0;
}
