#include <gmock/gmock.h>

#include <set>

#include "../set/s21_set.h"

using namespace std;

TEST(TestsSet, set_init_list) {
  s21::set<int> m{3, 2, 5};
  s21::set<int>::iterator it = m.begin();

  ASSERT_TRUE(*it == 2);
  it++;
  ASSERT_TRUE(*it == 3);
  it++;
  ASSERT_TRUE(*it == 5);
  ASSERT_TRUE(m.size() == 3);
}

TEST(TestsSet, set_insert) {
  s21::set<int> m;
  m.insert(5);
  m.insert(1);
  m.insert(4);
  m.insert(3);
  m.insert(2);

  ASSERT_TRUE(m.size() == 5);

  int count = 1;
  for (s21::set<int>::iterator it = m.begin(); it != m.end(); ++it) {
    ASSERT_TRUE(*it == count);
    count++;
  }
}

TEST(TestsSet, set_copy_constructor) {
  s21::set<int> m;
  m.insert(5);
  m.insert(1);
  m.insert(4);
  m.insert(3);
  m.insert(2);

  s21::set<int> copy(m);
  auto it_m = m.begin();
  auto it_copy = copy.begin();

  ASSERT_TRUE(m.size() == copy.size());
  for (; it_m != m.end(); it_m++, it_copy++) {
    ASSERT_TRUE(it_m.it->data == it_copy.it->data);
  }
}

TEST(TestsSet, set_move_constructor) {
  s21::set<int> m;
  m.insert(5);
  m.insert(1);
  m.insert(4);
  m.insert(3);
  m.insert(2);

  s21::set<int> move_m(move(m));

  ASSERT_TRUE(move_m.size() == 5);
  ASSERT_TRUE(m.size() == 0);

  int count = 1;
  for (s21::set<int>::iterator it = move_m.begin(); it != move_m.end(); ++it) {
    ASSERT_TRUE(*it == count);
    count++;
  }
}

TEST(TestsSet, set_operator_eq) {
  s21::set<int> m;
  m.insert(5);
  m.insert(1);
  m.insert(4);
  m.insert(3);
  m.insert(2);

  s21::set<int> copy;
  copy = m;
  auto it_m = m.begin();
  auto it_copy = copy.begin();

  ASSERT_TRUE(m.size() == copy.size());
  for (; it_m != m.end(); it_m++, it_copy++) {
    ASSERT_TRUE(it_m.it->data == it_copy.it->data);
    ASSERT_TRUE(it_m.it->data == it_copy.it->data);
  }
}

TEST(TestsSet, set_operator_eq_move) {
  s21::set<int> m;
  m.insert(5);
  m.insert(1);
  m.insert(4);
  m.insert(3);
  m.insert(2);

  s21::set<int> move_m;
  move_m = move(m);

  ASSERT_TRUE(move_m.size() == 5);
  ASSERT_TRUE(m.size() == 0);

  int count = 1;
  for (s21::set<int>::iterator it = move_m.begin(); it != move_m.end(); ++it) {
    ASSERT_TRUE(*it == count);
    count++;
  }
}

TEST(TestsSet, set_swap) {
  s21::set<int> m1{3, 2, 5};
  s21::set<int> m2{5, 7, 3, 4, 8, 6, 2, 1};

  s21::set<int> buffer_m1{3, 2, 5};
  s21::set<int> buffer_m2{5, 7, 3, 4, 8, 6, 2, 1};

  m1.swap(m2);

  ASSERT_TRUE(m1.size() == buffer_m2.size());
  ASSERT_TRUE(m2.size() == buffer_m1.size());
}

TEST(TestsSet, set_merge) {
  s21::set<int> m{3, 2, 5};
  s21::set<int> m2{1, 4};

  m.merge(m2);
  ASSERT_TRUE(m.size() == 5);
  int count = 1;
  for (s21::set<int>::iterator it = m.begin(); it != m.end(); ++it) {
    ASSERT_TRUE(*it == count);
    count++;
  }
}

TEST(TestsSet, set_contains) {
  s21::set<int> m{0, 9, 5, 7, 3};

  ASSERT_TRUE(m.size() == 5);
  for (auto x : {0, 3, 5, 7, 9}) {
    ASSERT_TRUE(m.contains(x) == true);
  }
  for (auto x : {2, 11, 26}) {
    ASSERT_TRUE(m.contains(x) == false);
  }
}

TEST(TestsSet, set_find) {
  s21::set<int> m{0, 9, 5, 7, 3};

  ASSERT_TRUE(m.size() == 5);
  s21::set<int>::iterator it = m.begin();
  ASSERT_TRUE(m.find(0) == it);
  it++;
  ASSERT_TRUE(m.find(3) == it);
  it++;
  ASSERT_TRUE(m.find(5) == it);
  it++;
  ASSERT_TRUE(m.find(7) == it);
  it++;
  ASSERT_TRUE(m.find(9) == it);
}

TEST(TestsSet, set_erase) {
  s21::set<int> m{5, 1, 4, 3, 2};
  ASSERT_TRUE(m.size() == 5);

  auto it = m.begin();
  m.erase(it);

  ASSERT_TRUE(m.size() == 4);

  int count = 2;
  for (s21::set<int>::iterator it = m.begin(); it != m.end(); ++it) {
    ASSERT_TRUE(*it == count);
    count++;
  }
}

TEST(TestsSet, max_size) {
  s21::set<int> s21_set{3, 2, 5};
  std::set<int> std_set{3, 2, 5};
  ASSERT_TRUE(s21_set.max_size() == std_set.max_size());
}

TEST(TestsSet, emplace) {
  s21::set<int> m{7, 9, 0, 3, 5};

  ASSERT_TRUE(m.size() == 5);
  m.emplace(4);

  const int x[] = {0, 3, 4, 5, 7, 9};
  int i = 0;
  for (s21::set<int>::iterator it = m.begin(); it != m.end(); ++it) {
    ASSERT_TRUE(*it == x[i]);
    i++;
  }
}

TEST(TestsSet, set_erase_1) {
  s21::set<int> m{5, 3, 6, 4, 1, 2, 18, 7, 19, 10, 9, 12};
  ASSERT_TRUE(m.size() == 12);

  auto it = m.begin();
  ++it;
  ++it;
  ++it;
  m.erase(it);
  const int x[] = {1, 2, 3, 5, 6, 7, 9, 10, 12, 18, 19};
  int i = 0;
  ASSERT_TRUE(m.size() == 11);
  for (s21::set<int>::iterator it = m.begin(); it != m.end(); ++it) {
    ASSERT_TRUE(*it == x[i]);
    i++;
  }
}

TEST(TestsSet, set_erase_2) {
  s21::set<int> m{5, 3, 6, 4, 1, 2, 18, 7, 19, 10, 9, 12};

  ASSERT_TRUE(m.size() == 12);

  auto it = m.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  m.erase(it);
  const int x[] = {1, 2, 3, 4, 5, 6, 9, 10, 12, 18, 19};

  int i = 0;
  ASSERT_TRUE(m.size() == 11);
  for (s21::set<int>::iterator it = m.begin(); it != m.end(); ++it) {
    ASSERT_TRUE(*it == x[i]);
    i++;
  }
}

TEST(TestsSet, set_erase_3) {
  s21::set<int> m{5, 3, 6, 4, 1, 2, 18, 7, 19, 10, 9, 12};

  ASSERT_TRUE(m.size() == 12);

  auto it = m.begin();
  ++it;
  ++it;
  m.erase(it);

  const int x[] = {1, 2, 4, 5, 6, 7, 9, 10, 12, 18, 19};
  int i = 0;
  ASSERT_TRUE(m.size() == 11);
  for (s21::set<int>::iterator it = m.begin(); it != m.end(); ++it) {
    ASSERT_TRUE(*it == x[i]);
    i++;
  }
}

TEST(TestsSet, set_erase_4) {
  s21::set<int> m{5, 3, 6, 4, 1, 2, 18, 7, 20, 10, 9, 12, 21};
  ASSERT_TRUE(m.size() == 13);

  auto it = m.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  m.erase(it);

  ASSERT_TRUE(m.size() == 12);
  const int x[] = {1, 2, 3, 4, 5, 6, 7, 9, 10, 12, 20, 21};
  int i = 0;
  for (s21::set<int>::iterator it = m.begin(); it != m.end(); ++it) {
    ASSERT_TRUE(*it == x[i]);
    i++;
  }
}

TEST(TestsSet, set_erase_5) {
  s21::set<int> m;
  auto it = m.begin();
  m.erase(it);

  ASSERT_TRUE(m.size() == 0);
}

TEST(TestsSet, set_erase_6) {
  s21::set<int> m{5, 3, 6, 4, 1, 2, 18, 7, 19, 10, 9, 12};
  m.insert(18);
  ASSERT_TRUE(m.size() == 12);

  auto it = m.begin();
  ++it;
  ++it;
  ++it;
  m.erase(it);

  ASSERT_TRUE(m.size() == 11);
  const int x[] = {1, 2, 3, 5, 6, 7, 9, 10, 12, 18, 19};
  int i = 0;
  for (s21::set<int>::iterator it = m.begin(); it != m.end(); ++it) {
    ASSERT_TRUE(*it == x[i]);
    i++;
  }
}

TEST(TestsSet, cont) {
  s21::set<int> m;
  ASSERT_TRUE(m.contains(5) == false);
}
