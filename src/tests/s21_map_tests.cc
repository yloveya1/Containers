#include <gmock/gmock.h>

#include <map>

#include "../map/s21_map.h"

using namespace std;

TEST(Map, map_init_list) {
  s21::map<int, char> m{{3, '3'}, {2, '2'}, {5, '5'}};

  ASSERT_TRUE(m[3] == '3');
  ASSERT_TRUE(m[2] == '2');
  ASSERT_TRUE(m[5] == '5');
  ASSERT_TRUE(m[10] == char());
  m[2] = '1';
  ASSERT_TRUE(m[2] == '1');
  ASSERT_TRUE(m.size() == 4);
  auto check = m.insert(pair<int, char>(3, '0'));
  ASSERT_TRUE(check.second == false);
}

TEST(Map, map_insert_or_assign) {
  s21::map<int, int> m;
  m.insert(pair<int, int>(5, 5));
  m.insert(pair<int, int>(6, 6));
  m.insert(pair<int, int>(3, 3));
  m.insert(pair<int, int>(4, 4));
  m.insert(pair<int, int>(1, 1));
  m.insert(pair<int, int>(2, 2));
  m.insert(pair<int, int>(18, 18));
  m.insert(pair<int, int>(7, 7));
  m.insert(pair<int, int>(19, 19));
  m.insert(pair<int, int>(10, 10));
  m.insert(pair<int, int>(9, 9));
  m.insert(pair<int, int>(12, 12));

  m.insert_or_assign(3, 33);

  ASSERT_TRUE(m[3] == 33);
  ASSERT_TRUE(m.size() == 12);

  for (int x : {1, 2, 3, 4, 5, 6, 7, 9, 10, 12, 18, 19}) {
    if (x == 3) {
      ASSERT_TRUE(m[x] == 33);
    } else {
      ASSERT_TRUE(m[x] == x);
    }
  }
}

TEST(Map, map_copy_constructor) {
  s21::map<int, int> m;
  m.insert(pair<int, int>(5, 5));
  m.insert(pair<int, int>(6, 6));
  m.insert(pair<int, int>(3, 3));
  m.insert(pair<int, int>(4, 4));
  m.insert(pair<int, int>(1, 1));
  m.insert(pair<int, int>(2, 2));
  m.insert(pair<int, int>(18, 18));
  m.insert(pair<int, int>(7, 7));
  m.insert(pair<int, int>(19, 19));
  m.insert(pair<int, int>(10, 10));
  m.insert(pair<int, int>(9, 9));
  m.insert(pair<int, int>(12, 12));

  s21::map<int, int> copy(m);
  auto it_m = m.begin();
  auto it_copy = copy.begin();

  ASSERT_TRUE(m.size() == copy.size());
  for (; it_m != m.end(); it_m++, it_copy++) {
    ASSERT_TRUE(it_m.it->data.first == it_copy.it->data.first);
    ASSERT_TRUE(it_m.it->data.second == it_copy.it->data.second);
  }
}

TEST(Map, map_move_constructor) {
  s21::map<int, int> m;
  m.insert(pair<int, int>(5, 5));
  m.insert(pair<int, int>(6, 6));
  m.insert(pair<int, int>(3, 3));
  m.insert(pair<int, int>(4, 4));
  m.insert(pair<int, int>(1, 1));
  m.insert(pair<int, int>(2, 2));
  m.insert(pair<int, int>(18, 18));
  m.insert(pair<int, int>(7, 7));
  m.insert(pair<int, int>(19, 19));
  m.insert(pair<int, int>(10, 10));
  m.insert(pair<int, int>(9, 9));
  m.insert(pair<int, int>(12, 12));

  s21::map<int, int> move_m(move(m));

  ASSERT_TRUE(move_m.size() == 12);
  ASSERT_TRUE(m.size() == 0);

  for (int x : {1, 2, 3, 4, 5, 6, 7, 9, 10, 12, 18, 19}) {
    ASSERT_TRUE(move_m[x] == x);
  }
}

TEST(Map, map_operator_eq) {
  s21::map<int, int> m;
  m.insert(pair<int, int>(5, 5));
  m.insert(pair<int, int>(6, 6));
  m.insert(pair<int, int>(3, 3));
  m.insert(pair<int, int>(4, 4));
  m.insert(pair<int, int>(1, 1));
  m.insert(pair<int, int>(2, 2));
  m.insert(pair<int, int>(18, 18));
  m.insert(pair<int, int>(7, 7));
  m.insert(pair<int, int>(19, 19));
  m.insert(pair<int, int>(10, 10));
  m.insert(pair<int, int>(9, 9));
  m.insert(pair<int, int>(12, 12));

  s21::map<int, int> copy;
  copy = m;
  auto it_m = m.begin();
  auto it_copy = copy.begin();

  ASSERT_TRUE(m.size() == copy.size());
  for (; it_m != m.end(); it_m++, it_copy++) {
    ASSERT_TRUE(it_m.it->data.first == it_copy.it->data.first);
    ASSERT_TRUE(it_m.it->data.second == it_copy.it->data.second);
  }
}

TEST(Map, map_operator_eq_move) {
  s21::map<int, int> m;
  m.insert(pair<int, int>(5, 5));
  m.insert(pair<int, int>(6, 6));
  m.insert(pair<int, int>(3, 3));
  m.insert(pair<int, int>(4, 4));
  m.insert(pair<int, int>(1, 1));
  m.insert(pair<int, int>(2, 2));
  m.insert(pair<int, int>(18, 18));
  m.insert(pair<int, int>(7, 7));
  m.insert(pair<int, int>(19, 19));
  m.insert(pair<int, int>(10, 10));
  m.insert(pair<int, int>(9, 9));
  m.insert(pair<int, int>(12, 12));

  s21::map<int, int> move_m;
  move_m = move(m);

  ASSERT_TRUE(move_m.size() == 12);
  ASSERT_TRUE(m.size() == 0);

  for (int x : {1, 2, 3, 4, 5, 6, 7, 9, 10, 12, 18, 19}) {
    ASSERT_TRUE(move_m[x] == x);
  }
}

TEST(Map, map_at) {
  s21::map<int, char> m{{3, '3'}, {2, '2'}, {5, '5'}};

  m.at(2) = '9';
  ASSERT_TRUE(m[2] == '9');
  m.at(2) = '0';
  ASSERT_TRUE(m[2] == '0');
  m.at(5) = '4';
  ASSERT_TRUE(m[5] == '4');
}

TEST(Map, map_at_throw) {
  s21::map<int, char> m{{3, '3'}, {2, '2'}, {5, '5'}};

  EXPECT_ANY_THROW(m.at('1') = '1');
}

TEST(Map, map_at_throw_empty) {
  s21::map<int, char> m;
  std::map<int, char> check;

  EXPECT_ANY_THROW(m.at('1') = '1');
}

TEST(Map, map_swap) {
  s21::map<int, int> m1{{3, 3}, {2, 2}, {5, 5}};
  s21::map<int, int> m2{{5, 5}, {7, 7}, {3, 3}, {4, 4},
                        {8, 8}, {6, 6}, {2, 2}, {1, 1}};

  s21::map<int, int> buffer_m1{{3, 3}, {2, 2}, {5, 5}};
  s21::map<int, int> buffer_m2{{5, 5}, {7, 7}, {3, 3}, {4, 4},
                               {8, 8}, {6, 6}, {2, 2}, {1, 1}};

  m1.swap(m2);

  ASSERT_TRUE(m1.size() == buffer_m2.size());
  ASSERT_TRUE(m2.size() == buffer_m1.size());

  for (int x : {1, 2, 3, 4, 5, 6, 7, 8}) {
    ASSERT_TRUE(m1[x] == x);
  }

  for (auto x : {2, 3, 5}) {
    ASSERT_TRUE(m2[x] == x);
  }
}

TEST(Map, map_insert_key_obj) {
  s21::map<int, int> m{{3, 3}, {2, 2}, {5, 5}};
  m.insert(0, 0);
  m.insert(9, 9);
  m.insert(25, 25);
  m.insert(7, 7);
  m.insert(1, 1);
  m.insert(-1, -1);

  ASSERT_TRUE(m.size() == 9);
  for (auto x : {-1, 0, 1, 2, 3, 5, 7, 9, 25}) {
    ASSERT_TRUE(m[x] == x);
  }
}

TEST(Map, map_merge) {
  s21::map<int, int> m{{3, 3}, {2, 2}, {5, 5}};
  s21::map<int, int> m2{{0, 0}, {9, 9}, {5, 55}, {7, 7}, {3, 33}};

  m.merge(m2);
  ASSERT_TRUE(m.size() == 6);
  for (auto x : {0, 2, 3, 5, 7, 9}) {
    ASSERT_TRUE(m[x] == x);
  }
}

TEST(Map, map_contains) {
  s21::map<int, int> m{{0, 0}, {9, 9}, {5, 55}, {7, 7}, {3, 33}};

  ASSERT_TRUE(m.size() == 5);
  for (auto x : {0, 3, 5, 7, 9}) {
    ASSERT_TRUE(m.contains(x) == true);
  }
  for (auto x : {2, 11, 26}) {
    ASSERT_TRUE(m.contains(x) == false);
  }
}

TEST(Map, map_erase_1) {
  s21::map<int, int> m{{5, 5},   {3, 3}, {6, 6},   {4, 4},   {1, 1}, {2, 2},
                       {18, 18}, {7, 7}, {19, 19}, {10, 10}, {9, 9}, {12, 12}};
  ASSERT_TRUE(m.size() == 12);

  auto it = m.begin();
  ++it;
  ++it;
  ++it;
  s21::map<int, int>::const_iterator const_it(it);
  m.erase(it);

  ASSERT_TRUE(m.size() == 11);

  for (auto x : {1, 2, 3, 4, 5, 6, 7, 9, 10, 12, 18, 19}) {
    if (x == 4) {
      ASSERT_TRUE(m.contains(x) == false);
    } else {
      ASSERT_TRUE(m[x] == x);
    }
  }
}

TEST(Map, map_erase_2) {
  s21::map<int, int> m{{5, 5},   {3, 3}, {6, 6},   {4, 4},   {1, 1}, {2, 2},
                       {18, 18}, {7, 7}, {19, 19}, {10, 10}, {9, 9}, {12, 12}};
  ASSERT_TRUE(m.size() == 12);

  auto it = m.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  m.erase(it);

  ASSERT_TRUE(m.size() == 11);

  for (auto x : {1, 2, 3, 4, 5, 6, 7, 9, 10, 12, 18, 19}) {
    if (x == 7) {
      ASSERT_TRUE(m.contains(x) == false);
    } else {
      ASSERT_TRUE(m[x] == x);
    }
  }
}

TEST(Map, map_erase_3) {
  s21::map<int, int> m{{5, 5},   {3, 3}, {6, 6},   {4, 4},   {1, 1}, {2, 2},
                       {18, 18}, {7, 7}, {19, 19}, {10, 10}, {9, 9}, {12, 12}};
  ASSERT_TRUE(m.size() == 12);

  auto it = m.begin();
  ++it;
  ++it;
  m.erase(it);

  ASSERT_TRUE(m.size() == 11);

  for (auto x : {1, 2, 3, 4, 5, 6, 7, 9, 10, 12, 18, 19}) {
    if (x == 3) {
      ASSERT_TRUE(m.contains(x) == false);
    } else {
      ASSERT_TRUE(m[x] == x);
    }
  }
}

TEST(Map, map_erase_4) {
  s21::map<int, int> m{{5, 5}, {3, 3},   {6, 6},  {4, 4},   {1, 1},
                       {2, 2}, {18, 18}, {7, 7},  {20, 20}, {10, 10},
                       {9, 9}, {12, 12}, {21, 21}};
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

  for (auto x : {1, 2, 3, 4, 5, 6, 7, 9, 10, 12, 18, 20, 21}) {
    if (x == 18) {
      ASSERT_TRUE(m.contains(x) == false);
    } else {
      ASSERT_TRUE(m[x] == x);
    }
  }
}

TEST(Map, map_erase_5) {
  s21::map<int, int> m;
  auto it = m.begin();
  m.erase(it);

  ASSERT_TRUE(m.size() == 0);
}

TEST(Map, map_erase_6) {
  s21::map<int, int> m{{5, 5},   {3, 3}, {6, 6},   {4, 4},   {1, 1}, {2, 2},
                       {18, 18}, {7, 7}, {19, 19}, {10, 10}, {9, 9}, {12, 12}};
  ASSERT_TRUE(m.size() == 12);

  auto it = m.begin();
  ++it;
  ++it;
  ++it;
  m.erase(it);

  ASSERT_TRUE(m.size() == 11);

  for (auto x : {1, 2, 3, 4, 5, 6, 7, 9, 10, 12, 18, 19}) {
    if (x == 4) {
      ASSERT_TRUE(m.contains(x) == false);
    } else {
      ASSERT_TRUE(m[x] == x);
    }
  }
}

TEST(Map, map_emplace) {
  s21::map<int, int> m{{0, 0}, {9, 9}, {5, 5}, {7, 7}, {3, 3}};

  ASSERT_TRUE(m.size() == 5);
  auto check = m.emplace(std::pair<int, int>(4, 4));

  for (auto x : {0, 3, 5, 7, 9, 4}) {
    ASSERT_TRUE(m[x] == x);
  }
}

TEST(Map, map_max_size) {
  s21::map<int, int> m;
  std::map<int, int> check;
  ASSERT_TRUE(m.max_size() == check.max_size());
}

TEST(Map, map_erase_7) {
  s21::map<int, int> m{{5, 5},   {3, 3}, {6, 6},   {4, 4},   {1, 1}, {2, 2},
                       {18, 18}, {7, 7}, {19, 19}, {10, 10}, {9, 9}, {12, 12}};
  ASSERT_TRUE(m.size() == 12);

  auto it = m.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  m.erase(it);

  ASSERT_TRUE(m.size() == 11);

  const int x[] = {1, 2, 3, 4, 5, 6, 9, 10, 12, 18, 19};
  int i = 0;
  for (s21::map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {
    ASSERT_TRUE(it.it->data.first == x[i]);
    i++;
  }
}

TEST(Map, map_erase_8) {
  s21::map<int, int> m{{5, 5},   {3, 3}, {6, 6},   {4, 4},   {1, 1}, {2, 2},
                       {18, 18}, {7, 7}, {19, 19}, {10, 10}, {9, 9}, {12, 12}};
  ASSERT_TRUE(m.size() == 12);

  auto it = m.begin();
  ++it;
  ++it;
  m.erase(it);

  ASSERT_TRUE(m.size() == 11);

  const int x[] = {1, 2, 4, 5, 6, 7, 9, 10, 12, 18, 19};
  int i = 0;

  for (s21::map<int, int>::const_iterator it = m.begin(); it != m.end(); ++it) {
    ASSERT_TRUE(it.getNode()->data.first == x[i]);
    i++;
  }

  i = 10;
  for (s21::map<int, int>::const_iterator it = --(m.end()); it != m.begin();
       --it) {
    ASSERT_TRUE(it.getNode()->data.first == x[i]);
    i--;
  }
}

TEST(Map, map_erase_9) {
  s21::map<int, int> m{{5, 5}, {3, 3},   {6, 6},  {4, 4},   {1, 1},
                       {2, 2}, {18, 18}, {7, 7},  {20, 20}, {10, 10},
                       {9, 9}, {12, 12}, {21, 21}};
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
  it--;
  ++it;
  m.erase(it);

  ASSERT_TRUE(m.size() == 12);

  const int x[] = {1, 2, 3, 4, 5, 6, 7, 9, 10, 12, 20, 21};
  int i = 11;

  for (s21::map<int, int>::iterator it = --(m.end()); !(it == m.begin());
       --it) {
    ASSERT_TRUE(it.it->data.first == x[i]);
    i--;
  }
}
