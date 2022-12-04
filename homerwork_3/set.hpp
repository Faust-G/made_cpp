#pragma once

#include <bits/stdc++.h>

using std::cout, std::cin, std::ios, std::string, std::to_string, std::cerr,
    std::max, std::swap, std::vector;

template <typename T> class Set {
private:
  int num_obj = 0;
  struct Tree {
    T val;
    int sz = 1;
    Tree *right = nullptr;
    Tree *left = nullptr;
    const T &operator*() { return val; }
  };
  void update_height(Tree *&cur) {
    if (cur == nullptr)
      return;
    int szl = (cur->left ? cur->left->sz : 0),
        szr = (cur->right ? cur->right->sz : 0);
    cur->sz = std::max(szl, szr) + 1;
  }
  void right_fix(Tree *&cur) {
    Tree *left = cur->left;
    swap(cur->val, left->val);
    cur->left = left->left;
    Tree *r = cur->right;
    cur->right = left;
    left->left = left->right;
    left->right = r;
    update_height(cur->left);
    update_height(cur->right);
    update_height(cur);
  }
  void left_fix(Tree *&cur) {
    Tree *right = cur->right;
    swap(cur->val, right->val);
    cur->right = right->right;
    Tree *l = cur->left;
    cur->left = right;
    right->right = right->left;
    right->left = l;
    update_height(cur->left);
    update_height(cur->right);
    update_height(cur);
  }
  int get_size(Tree *&cur) { return (cur ? cur->sz : 0); }
  void balance(Tree *&cur) {
    if (cur == nullptr)
      return;
    int szl = get_size(cur->left), szr = get_size(cur->right);
    int diff = szl - szr;
    if (abs(diff) <= 1)
      return;
    if (diff < 0) { // левое вращение
      Tree *&q = cur->right;
      int h_s = 0, h_d = 0;
      h_s = get_size(q->left);
      h_d = get_size(q->right);
      if (h_s > h_d)
        right_fix(q);
      left_fix(cur);
    } else {
      Tree *&q = cur->left;
      int h_s = 0, h_d = 0;
      h_s = get_size(q->right);
      h_d = get_size(q->left);
      if (h_s > h_d)
        left_fix(q);
      right_fix(cur);
    }
  }
  void __insert(Tree *&cur, const T &val) {
    if (cur == nullptr) {
      cur = new Tree{val};
      ++num_obj;
    } else if (cur->val < val)
      __insert(cur->right, val);
    else if (val < cur->val)
      __insert(cur->left, val);
    balance(cur);
    update_height(cur);
  }
  Tree *__exist(Tree *&cur, const T &val) {
    if (cur == nullptr)
      return nullptr;
    if (cur->val == val)
      return cur;
    if (cur->val < val)
      return __exist(cur->right, val);
    return __exist(cur->left, val);
  }
  void __erase(Tree *&cur, const T &val) {
    if (cur == nullptr)
      return;
    if (val < cur->val)
      __erase(cur->left, val);
    else if (cur->val < val)
      __erase(cur->right, val);
    else if (cur->right == nullptr && cur->left == nullptr) {
      delete cur;
      cur = nullptr;
      --num_obj;
    } else {
      bool fg = (cur->left == nullptr);
      Tree *it = cur->left;
      if (fg)
        it = cur->right;
      while (it->right != nullptr)
        it = it->right;
      cur->val = it->val;
      if (fg)
        __erase(cur->right, cur->val);
      else
        __erase(cur->left, cur->val);
    }
    balance(cur);
    update_height(cur);
  }
  const Tree *__lower_bound(Tree *cur, const T &val) const {
    Tree *res = cur;
    while (cur != nullptr) {
      if (!(cur->val < val)) {
        res = cur;
        cur = cur->left;
      } else
        cur = cur->right;
    }
    if (res != nullptr && !(res->val < val))
      return res;
    return nullptr;
  }
  const Tree *__find(Tree *cur, const T &k) const {
    if (cur == nullptr)
      return nullptr;
    if (cur->val < k)
      return __find(cur->right, k);
    if (k < cur->val)
      return __find(cur->left, k);
    return cur;
  }
  Tree *vertex = nullptr;
  void copy(const Set<T> &x) {
    std::queue<Tree *> q;
    q.push(x.vertex);
    while (q.size() > 0) {
      Tree *&p = q.front();
      q.pop();
      if (p == nullptr)
        continue;
      this->insert(p->val);
      q.push(p->left);
      q.push(p->right);
    }
  }
  void __to_vector(vector<T> &v, Tree *cur) const {
    if (cur == nullptr)
      return;
    __to_vector(v, cur->left);
    v.emplace_back(cur->val);
    __to_vector(v, cur->right);
  }

public:
  const Tree *end() const { return nullptr; }
  Set() = default;
  Set(const T *begin, const T *end) {
    while (begin != end) {
      this->insert(*begin);
      ++begin;
    }
  }
  Set(std::initializer_list<T> l) {
    for (auto &i : l)
      this->insert(i);
  }
  Set(const Set<T> &x) { copy(x); }
  Set &operator=(const Set<T> &x) {
    if (&x != this) {
      this->~Set();
      copy(x);
    }
    return *this;
  }
  void insert(const T &x) { __insert(vertex, x); }
  int size() const { return num_obj; }
  int empty() const { return num_obj == 0; }
  void erase(const T &x) { __erase(vertex, x); }
  vector<T> to_vector() const {
    vector<T> res;
    __to_vector(res, vertex);
    return res;
  }
  const Tree *lower_bound(const T &x) const { return __lower_bound(vertex, x); }
  const Tree *find(const T &x) const { return __find(vertex, x); }
  ~Set() {
    std::queue<Tree *> q;
    q.push(this->vertex);
    while (q.size() > 0) {
      Tree *&p = q.front();
      q.pop();
      if (p == nullptr)
        continue;
      q.push(p->left);
      q.push(p->right);
      delete p;
    }
    num_obj = 0;
    vertex = nullptr;
  }
};