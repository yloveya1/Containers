#include <gmock/gmock.h>

#include <array>

#include "../array/s21_array.h"

TEST(Array, array_init_list) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {1, 2, 3, 4, 5};

  for (int i = 0; i < 10; i++) {
    ASSERT_TRUE(a[i] == b[i]);
  }
}

TEST(Array, array_copy_constructor) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {1, 2, 3, 4, 5};

  std::array<int, 10> copy_a(a);
  s21::array<int, 10> copy_b(b);

  for (int i = 0; i < 10; i++) {
    ASSERT_TRUE(a[i] == b[i]);
    ASSERT_TRUE(copy_a[i] == copy_b[i]);
  }
}

TEST(Array, array_move_constructor) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {1, 2, 3, 4, 5};

  std::array<int, 10> move_a(std::move(a));
  s21::array<int, 10> move_b(std::move(b));

  for (int i = 0; i < 10; i++) {
    ASSERT_TRUE(a[i] == b[i]);
    ASSERT_TRUE(move_a[i] == move_b[i]);
  }
}

TEST(Array, array_at) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {1, 2, 3, 4, 5};

  for (int i = 0; i < 10; i++) {
    ASSERT_TRUE(a.at(i) == b.at(i));
  }
}

TEST(Array, array_swap) {
  s21::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {11, 22, 33, 44, 55};

  s21::array<int, 10> copy_a(a);
  s21::array<int, 10> copy_b(b);

  a.swap(b);

  for (int i = 0; i < 10; i++) {
    ASSERT_TRUE(a[i] == copy_b[i]);
    ASSERT_TRUE(b[i] == copy_a[i]);
  }
}

TEST(Array, array_fill) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {1, 2, 3, 4, 5};

  a.fill(55);
  b.fill(55);

  for (int i = 0; i < 10; i++) {
    ASSERT_TRUE(a[i] == b[i]);
  }
}

TEST(Array, array_operator_eq_move) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  std::array<int, 10> a1 = {11, 22, 33, 44, 55};

  s21::array<int, 10> b = {1, 2, 3, 4, 5};
  s21::array<int, 10> b1 = {11, 22, 33, 44, 55};

  a = std::move(a1);
  b = std::move(b1);

  for (int i = 0; i < 10; i++) {
    ASSERT_TRUE(a[i] == b[i]);
    ASSERT_TRUE(a1[i] == b1[i]);
  }
}

TEST(Array, array_size) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {1, 2, 3, 4, 5};

  ASSERT_TRUE(a.size() == b.size());
}

TEST(Array, array_max_size) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {1, 2, 3, 4, 5};

  ASSERT_TRUE(a.max_size() == b.max_size());
}

TEST(Array, array_front) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {1, 2, 3, 4, 5};

  ASSERT_TRUE(a.front() == b.front());
}

TEST(Array, array_back) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {1, 2, 3, 4, 5};

  ASSERT_TRUE(a.back() == b.back());
}

TEST(Array, array_data) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {1, 2, 3, 4, 5};

  ASSERT_TRUE(*(a.data()) == *(b.data()));
}

TEST(Array, array_begin) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {1, 2, 3, 4, 5};

  ASSERT_TRUE(*(a.begin()) == *(b.begin()));
}

TEST(Array, array_end) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {1, 2, 3, 4, 5};

  ASSERT_TRUE(*(a.end() - 1) == *(b.end() - 1));
}

TEST(Array, array_not_empty) {
  std::array<int, 10> a = {1, 2, 3, 4, 5};
  s21::array<int, 10> b = {1, 2, 3, 4, 5};

  ASSERT_TRUE(a.empty() == b.empty());
}

TEST(Array, array_empty) {
  std::array<int, 0> a;
  s21::array<int, 0> b;

  ASSERT_TRUE(a.empty() == b.empty());
}

TEST(Array, array_list_const) {
  std::array<int, 3> a = {1, 2, 3};
  s21::array<int, 3> b = {1, 2, 3, 4, 5};
  for (int i = 0; i < 3; i++) {
    ASSERT_TRUE(a[i] == b[i]);
  }
}

TEST(Array, array_at_throw) {
  std::array<int, 3> a = {1, 2, 3};
  s21::array<int, 3> b = {1, 2, 3};

  int check_std = 0, check_s21 = 0;
  try {
    check_std = a.at(10);
  } catch (const std::exception &e) {
    check_std = 1;
  }

  try {
    check_s21 = b.at(10);
  } catch (const std::exception &e) {
    check_s21 = 1;
  }
  ASSERT_TRUE(check_std == check_s21);
}
