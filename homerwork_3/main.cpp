#include "set.hpp"

template <typename T> bool equal(const Set<T> &s, const std::set<T> &b) {
  if (s.size() != b.size())
    return false;
  auto a = s.to_vector();
  for (int i : a)
    if (b.find(i) == b.end())
      return false;
  return true;
}

int main() {
  for (int j = 0; j < 10; ++j) {
    std::set<int> s;
    Set<int> my_set;
    std::random_device r;
    std::vector<int> v{-3};
    for (int i = 0; i < 100000; ++i) {
      int op = r() % 3;
      int x = int(r() % 1000) - r() % 1000;
      if (op == 0) {
        s.insert(x);
        my_set.insert(x);
        v.push_back(x);
      }
      if (op == 1) {
        int k = r() % v.size();
        if (s.find(v[k]) != s.end())
          s.erase(v[k]);
        my_set.erase(v[k]);
      }
      if (op == 2) {
        auto res = s.lower_bound(x);
        auto my_res = my_set.lower_bound(x);
        assert((res == s.end() && my_res == nullptr) || (*res == my_res->val));
      }
      // assert(equal(my_set, s));
    }
  }
}