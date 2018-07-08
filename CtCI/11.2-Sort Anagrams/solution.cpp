#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool cmp(const string& a, const string& b) {
  int n = a.length();
  int m = b.length();
  if(n != m)
    return n < m;
  vector<int> cnt_a(256, 0), cnt_b(256, 0);
  for(auto x: a)
    cnt_a[x]++;
  for(auto y: b)
    cnt_b[y]++;
  for(int i = 0; i < 256; i++)
    if(cnt_a[i] != cnt_b[i])
      return cnt_a[i] < cnt_b[i];
  return true;
}


class Solution {
public:
  void sort_anagrams(vector<string>& s) {
    sort(s.begin(), s.end(), cmp);
  }
};


class Solution2 {
public:
  void sort_anagrams(vector<string>& s) {
    unordered_map<string, vector<string>> m;
    for(auto x: s) {
      string key = x;
      sort(key.begin(), key.end());
      m[key].push_back(x);
    }
    auto it = s.begin();
    for(auto p: m) {
      for(auto x: p.second) {
        *it = x;
        ++it;
      }
    }
  }
};

int main() {
  vector<string> s = {"abc", "gftr", "cab", "erdf", "rfgt", "bac", "jkui", "ikju", "rfde", "bba", "aba"};
  Solution2 sol;
  for(auto k: s)
    cout<<k<<endl;
  cout<<"----------"<<endl;
  sol.sort_anagrams(s);
  for(auto k: s)
    cout<<k<<endl;
  return 0;
}
