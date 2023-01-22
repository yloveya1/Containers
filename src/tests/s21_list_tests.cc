#include <gmock/gmock.h>

#include <iostream>
#include <iterator>
#include <list>

#include "../list/s21_list.h"
using namespace std;

TEST(List, copy_list) {
  s21::list<int> list_ = {1, 2, 3};
  s21::list<int> check(list_);
  ASSERT_TRUE(list_ == check);
}

TEST(List, sort_list) {
  s21::list<int> check = {-9, -7, -5, -3, -1, 0, 4, 8, 12, 16};
  s21::list<int> list_;
  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
      list_.push_front(i * 2);
    } else {
      list_.push_back(-i);
    }
  }
  list_.sort();
  ASSERT_TRUE((list_ == check) == true);
}

TEST(List, splice_list) {
  s21::list<int> a;
  auto it_a = a.cbegin();
  s21::list<int> b = {1, 7, 9, 15, -15, 155};
  b.pop_front();
  b.pop_back();
  s21::list<int> check(b);
  a.splice(it_a, b);
  ASSERT_TRUE((a == check) == true);
}

TEST(List, splice_list_2) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8};

  s21::list<int> b = {1, 7, 5};

  s21::list<int>::iterator it_a = a.begin();
  ++it_a;
  ++it_a;
  s21::list<int>::const_iterator const_it(it_a);
  a.splice(const_it, b);
  s21::list<int> check = {1, 2, 1, 7, 5, 3, 4, 5, 6, 7, 8};

  ASSERT_TRUE(a == check);
}

TEST(List, splice_list_to_head) {
  s21::list<int> a = {88};
  auto it_a = a.cbegin();
  s21::list<int> b = {7, 6, 5, 4};
  s21::list<int> check = {7, 6, 5, 4, 88};
  a.splice(it_a, b);
  ASSERT_TRUE((a == check) == true);
}

TEST(List, splice_list_to_middle) {
  s21::list<int> a = {88, 1, 3, 5, 9};
  auto it_a = a.cbegin();
  it_a.shift(3);
  s21::list<int> b = {0, -9};
  s21::list<int> check = {88, 1, 3, 0, -9, 5, 9};
  a.splice(it_a, b);
  ASSERT_TRUE((a == check) == true);
}

TEST(List, reverse) {
  s21::list<int> a;
  for (int i = 0; i < 15; i++) {
    a.push_back(i);
    if (i % 3 == 0) {
      a.pop_back();
    }
    if (i % 3 == 2) {
      a.pop_front();
    }
  }
  a.push_back(-1);
  a.reverse();
  s21::list<int> check = {-1, 14, 13, 11, 10, 8};
  ASSERT_TRUE((a == check) == true);
}

TEST(List, unique) {
  s21::list<int> a = {1, 1, 1, 2, 3, 3, 4, 6, 7, 9, 9, 9, 9};
  a.unique();
  auto it = a.end();
  a.erase(it);
  s21::list<int> check = {1, 2, 3, 4, 6, 7, 9};
  ASSERT_TRUE((a == check) == true);
}

TEST(List, erase) {
  s21::list<int> a = {1, 2, 3, 4, 5};
  auto it = a.begin();
  it.shift(3);
  --it;
  a.erase(it);
  s21::list<int> check = {1, 2, 4, 5};
  s21::list<int> check_1 = {1, 2, 3, 5};
  ASSERT_TRUE((a == check) == true);
  ASSERT_TRUE((a == check_1) == false);
}

TEST(List, init) {
  s21::list<int> a(3);
  a.push_back(5);
  s21::list<int> b;
  b.push_back(0);
  b.push_front(0);
  b.push_back(0);
  b.push_back(5);
  ASSERT_TRUE((a == b) == true);
}

TEST(List, merge_list) {
  s21::list<int> a = {1, 2, 4, 300};
  s21::list<int> b = move(a);
  s21::list<int> c = {-7, -5, 3, 125};
  s21::list<int> check = {-7, -5, 1, 2, 3, 4, 125, 300};
  c.merge(b);
  ASSERT_TRUE(a.size() == 0);
  ASSERT_TRUE(b.size() == 0);
  ASSERT_TRUE((c == check) == true);
  ASSERT_TRUE(c.max_size() == check.max_size());
}

TEST(List, emplace_back) {
  s21::list<int> a = {1, 2, 3, 4, 5};
  s21::list<int> b = {1, 2, 3, 4, 5, 6};
  a.emplace_back(6);
  ASSERT_TRUE(a == b);
}

TEST(List, emplace_front) {
  s21::list<int> a = {1, 2, 3, 4, 5};
  s21::list<int> b = {0, 1, 2, 3, 4, 5};
  a.emplace_front(0);
  ASSERT_TRUE(a == b);
}

TEST(List, emplace) {
  s21::list<int> a = {1, 2, 3, 4, 5};
  auto it = a.cbegin();
  ++it;
  s21::list<int> b = {1, 101, 2, 3, 4, 5};
  a.emplace(it, 101);
  ASSERT_TRUE(a == b);
}