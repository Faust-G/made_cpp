#include "set.hpp"
#include <gtest/gtest.h>

template <typename T> bool equal(const Set<T> &s, const std::set<T> &b) {
  if (s.size() != b.size())
    return false;
  auto a = s.to_vector();
  for (int i : a)
    if (b.find(i) == b.end())
      return false;
  return true;
}

TEST(My_Set, Test_constness) {
  const Set<int> s{-4, 5, 3, 0, 7};
  EXPECT_EQ(s.find(3) != nullptr, true);
  EXPECT_EQ(s.lower_bound(2)->val, 3);
  EXPECT_EQ(s.lower_bound(8), nullptr);
  EXPECT_EQ(s.lower_bound(-2)->val, 0);
  EXPECT_EQ(s.empty(), false);
  EXPECT_EQ(s.size(), 5);
}

TEST(My_Set, Test_copy_correctness) {
  int elems[] = {3, 3, -1, 6, 0, 0, 17, -5, 4, 2};
  Set<int> s1(elems, elems + 10);
  std::set<int> set_elems(elems, elems + 10);
  Set<int> s2 = s1;
  s2.insert(5);
  s2.insert(18);
  s2.insert(-2);
  EXPECT_EQ(equal(s1, set_elems), true);
  set_elems.insert(5);
  set_elems.insert(18);
  set_elems.insert(-2);
  s1 = s2;
  s2.insert(19);
  EXPECT_EQ(equal(s1, set_elems), true);
}

TEST(My_Set, check_empty) {
  Set<std::string> s;
  EXPECT_EQ(s.empty(), true);
  std::string elem("abacaba");
  s.insert(elem);
  EXPECT_EQ(s.lower_bound("aac")->val, elem);
  Set<std::string> empty;
  Set<std::string> s2{"opa"};
  s2 = empty;
  EXPECT_EQ(s2.size(), 0);
  Set<std::string> s3(s2);
  EXPECT_EQ(s3.empty(), true);
}
struct StrangeInt {
  int x;
  static int counter;
  StrangeInt() { ++counter; }
  StrangeInt(int x) : x(x) { ++counter; }
  StrangeInt(const StrangeInt &rs) : x(rs.x) { ++counter; }
  bool operator<(const StrangeInt &rs) const { return x < rs.x; }

  static void init() { counter = 0; }

  ~StrangeInt() { --counter; }

  friend std::ostream &operator<<(std::ostream &out, const StrangeInt &x) {
    out << x.x;
    return out;
  }
};
int StrangeInt::counter;

TEST(My_Set, operator_less) {
  Set<StrangeInt> s{-5, -3, -6, 13, 7, 1000, 963};
  auto it = s.lower_bound(999);
  EXPECT_EQ(it->val.x, 1000);
}

TEST(My_Set, destructor) {
  StrangeInt::init();
  {
    Set<StrangeInt> s{5, 4, 3, 2, 1, 0};
    EXPECT_EQ(s.size(), 6);
  }
  EXPECT_EQ(StrangeInt::counter, 0);
  {
    Set<StrangeInt> s{-3, 3, -2, 2, -1, 1};
    Set<StrangeInt> s1(s);
    s1.insert(0);
    Set<StrangeInt> s2(s1);
    EXPECT_EQ(s1.find(0) == nullptr, false);
    s1 = s;
    EXPECT_EQ(s1.find(0), nullptr);
  }
  EXPECT_EQ(StrangeInt::counter, 0);
}

TEST(My_Set, check_erase) {
  Set<std::string> s{"abacaba", "hello", "p"};
  s.erase("miss");
  s.erase("hello");
  EXPECT_EQ(s.size(), 2);
  s.erase("p");
  s.erase("1");
  s.erase("abacaba");
  s.erase("012");
  EXPECT_EQ(s.empty(), true);
}

TEST(My_set, stress) {
  for (int j = 0; j < 10; ++j) {
    std::set<int> s;
    Set<int> my_set;
    std::random_device r;
    std::vector<int> v{-3};
    for (int i = 0; i < 1e5; ++i) {
      int op = r() % 3;
      int x = int(r() % (int)1e5) - r() % (int)1e5;
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
        EXPECT_EQ((res == s.end() && my_res == nullptr) ||
                      (*res == my_res->val),
                  true);
      }
    }
  }
}