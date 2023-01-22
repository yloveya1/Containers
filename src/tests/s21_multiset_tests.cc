#include <gmock/gmock.h>

#include <set>

#include "../multiset/s21_multiset.h"

using namespace std;

TEST(TestsMultiset, multiset_init_list) {
  s21::multiset<int> m{1, 3, 4, 2, 2, 6};
  s21::multiset<int>::iterator it = m.begin();

  ASSERT_TRUE(*it == 1);
  it++;
  ASSERT_TRUE(*it == 2);
  it++;
  ASSERT_TRUE(*it == 2);
  it++;
  ASSERT_TRUE(*it == 3);
  it++;
  ASSERT_TRUE(*it == 4);
  it++;
  ASSERT_TRUE(*it == 6);
  ASSERT_TRUE(m.size() == 6);
}

TEST(TestsMultiset, multiset_insert) {
  int check[7] = {1, 2, 3, 3, 3, 4, 5};
  s21::multiset<int> m;
  m.insert(5);
  m.insert(3);
  m.insert(1);
  m.insert(4);
  m.insert(3);
  m.insert(2);
  m.insert(3);

  ASSERT_TRUE(m.size() == 7);

  int i = 0;
  for (s21::multiset<int>::iterator it = m.begin(); it != m.end(); ++it, i++) {
    ASSERT_TRUE(*it == check[i]);
  }
}

TEST(TestsMultiset, multiset_copy_constructor) {
  s21::multiset<int> m;
  m.insert(5);
  m.insert(3);
  m.insert(1);
  m.insert(4);
  m.insert(3);
  m.insert(2);
  m.insert(3);

  s21::multiset<int> copy(m);
  auto it_m = m.begin();
  auto it_copy = copy.begin();

  ASSERT_TRUE(m.size() == copy.size());
  for (; it_m != m.end(); it_m++, it_copy++) {
    ASSERT_TRUE(it_m.it->data == it_copy.it->data);
  }
}

TEST(TestsMultiset, multiset_move_constructor) {
  int check[7] = {1, 2, 3, 3, 3, 4, 5};
  s21::multiset<int> m;
  m.insert(5);
  m.insert(3);
  m.insert(1);
  m.insert(4);
  m.insert(3);
  m.insert(2);
  m.insert(3);

  s21::multiset<int> move_m(move(m));

  ASSERT_TRUE(move_m.size() == 7);
  ASSERT_TRUE(m.size() == 0);

  int i = 0;
  for (s21::multiset<int>::iterator it = move_m.begin(); it != move_m.end();
       ++it, i++) {
    ASSERT_TRUE(*it == check[i]);
  }
}

TEST(TestsMultiset, multiset_operator_eq) {
  s21::multiset<int> m;
  m.insert(5);
  m.insert(3);
  m.insert(1);
  m.insert(4);
  m.insert(3);
  m.insert(2);
  m.insert(3);

  s21::multiset<int> copy;
  copy = m;
  auto it_m = m.begin();
  auto it_copy = copy.begin();

  ASSERT_TRUE(m.size() == copy.size());
  for (; it_m != m.end(); it_m++, it_copy++) {
    ASSERT_TRUE(it_m.it->data == it_copy.it->data);
    ASSERT_TRUE(it_m.it->data == it_copy.it->data);
  }
}

TEST(TestsMultiset, multiset_operator_eq_move) {
  int check[7] = {1, 2, 3, 3, 3, 4, 5};
  s21::multiset<int> m;
  m.insert(5);
  m.insert(3);
  m.insert(1);
  m.insert(4);
  m.insert(3);
  m.insert(2);
  m.insert(3);

  s21::multiset<int> move_m;
  move_m = move(m);

  ASSERT_TRUE(move_m.size() == 7);
  ASSERT_TRUE(m.size() == 0);

  int i = 0;
  for (s21::multiset<int>::iterator it = move_m.begin(); it != move_m.end();
       ++it, i++) {
    ASSERT_TRUE(*it == check[i]);
  }
}

TEST(TestsMultiset, multiset_swap) {
  s21::multiset<int> m1{3, 2, 5};
  s21::multiset<int> m2{5, 7, 3, 4, 8, 6, 2, 1, 2, 2};

  s21::multiset<int> buffer_m1{3, 2, 5};
  s21::multiset<int> buffer_m2{5, 7, 3, 4, 8, 6, 2, 1, 2, 2};

  m1.swap(m2);

  ASSERT_TRUE(m1.size() == buffer_m2.size());
  ASSERT_TRUE(m2.size() == buffer_m1.size());
}

TEST(TestsMultiset, multiset_merge) {
  int check[7] = {1, 2, 3, 3, 3, 4, 5};
  s21::multiset<int> m{3, 2, 5};
  s21::multiset<int> m2{3, 1, 4, 3};

  m.merge(m2);
  ASSERT_TRUE(m.size() == 7);
  int i = 0;
  for (s21::multiset<int>::iterator it = m.begin(); it != m.end(); ++it, i++) {
    ASSERT_TRUE(*it == check[i]);
  }
}

TEST(TestsMultiset, multiset_contains) {
  s21::multiset<int> m{0, 9, 5, 7, 3, 3};

  ASSERT_TRUE(m.size() == 6);
  for (auto x : {0, 3, 5, 7, 9}) {
    ASSERT_TRUE(m.contains(x) == true);
  }
  for (auto x : {2, 11, 26}) {
    ASSERT_TRUE(m.contains(x) == false);
  }
}

TEST(TestsMultiset, multiset_find) {
  s21::multiset<int> m{0, 9, 5, 7, 3, 7};

  ASSERT_TRUE(m.size() == 6);
  s21::multiset<int>::iterator it = m.begin();
  ASSERT_TRUE(m.find(0) == it);
  it++;
  ASSERT_TRUE(m.find(3) == it);
  it++;
  ASSERT_TRUE(m.find(5) == it);
  it++;
  it++;
  ASSERT_TRUE(m.find(7) == it);
  it++;
  ASSERT_TRUE(m.find(9) == it);
}

TEST(TestsMultiset, multiset_erase) {
  s21::multiset<int> m{5, 1, 4, 3, 2, 5};
  ASSERT_TRUE(m.size() == 6);

  auto it = m.begin();
  m.erase(it);

  ASSERT_TRUE(m.size() == 5);

  int count = 2;
  for (s21::multiset<int>::iterator it = m.begin(); it != m.end(); ++it) {
    ASSERT_TRUE(*it == count);
    if (*it != 5) count++;
  }
}

TEST(TestsMultiset, max_size) {
  s21::multiset<int> s21_multiset{3, 2, 5};
  std::multiset<int> std_multiset{3, 2, 5};
  ASSERT_TRUE(s21_multiset.max_size() == std_multiset.max_size());
}