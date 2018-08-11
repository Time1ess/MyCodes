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

void test_sort(int n, void (*sort_func)(vector<int>&)) {
  while(n--) {
    auto nums = generate_nums(rand() % 100);
    auto expected_nums = nums;
    sort(expected_nums.begin(), expected_nums.end());
    sort_func(nums);
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

void heap_sort(vector<int>& nums) {
  int m = nums.size();
  while (m > 1) {
    for (int k = (m - 1) / 2; k >= 0; k--) {
      if (nums[k] < nums[2 * k]) {
        swap(nums[k], nums[2 * k]);
      }
      if (2 * k + 1 < m && nums[k] < nums[2 * k + 1]) {
        swap(nums[k], nums[2 * k + 1]);
      }
    }
    swap(nums[0], nums[m-1]);
    m--;
  }
}

int partition(vector<int>& nums, int s, int e) {
  int idx = s + rand() % (e - s);
  swap(nums[e], nums[idx]);
  idx = s - 1;
  for (int k = s; k < e; k++) {
    if (nums[k] < nums[e]) {
      ++idx;
      if (idx != k) {
        swap(nums[idx], nums[k]);
      }
    }
  }
  ++idx;
  swap(nums[idx], nums[e]);
  return idx;
}

void quick_sort(vector<int>& nums, int s, int e) {
  if (s >= e) {
    return;
  }
  int p = partition(nums, s, e);
  quick_sort(nums, s, p - 1);
  quick_sort(nums, p + 1, e);
}

void quick_sort(vector<int>& nums) {
  int n = nums.size();
  quick_sort(nums, 0, n - 1);
}

void merge(vector<int>& nums, int s, int m, int e) {
  vector<int> tmp(e - s, 0);
  int i = s, j = m, k = 0;
  while (i < m && j < e) {
    if (nums[i] < nums[j]) {
      tmp[k++] = nums[i++];
    } else {
      tmp[k++] = nums[j++];
    }
  }
  while (i < m) {
    tmp[k++] = nums[i++];
  }
  while (j < e) {
    tmp[k++] = nums[j++];
  }
  for (int idx = s; idx < e; idx++) {
    nums[idx] = tmp[idx-s];
  }
}

void merge_sort(vector<int>& nums, int s, int e) {
  if (s + 1 >= e) {
    return;
  }
  int m = s + (e - s) / 2;
  merge_sort(nums, s, m);
  merge_sort(nums, m, e);
  merge(nums, s, m, e);
}

void merge_sort(vector<int>& nums) {
  int n = nums.size();
  merge_sort(nums, 0, n);
}

int main() {
  srand(time(0));
  test_sort(10000, &heap_sort);
  test_sort(10000, &quick_sort);
  test_sort(10000, &merge_sort);
  return 0;
}
