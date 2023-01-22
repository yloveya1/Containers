#include <gmock/gmock.h>

#include <vector>

#include "../vector/s21_vector.h"

using namespace std;

TEST(TestsVector, vector_default_constructor) {
  s21::vector<int> v_s21;
  std::vector<int> v_std;

  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
}

TEST(TestsVector, vector_constructor_parametres) {
  s21::vector<int> v_s21(5);
  std::vector<int> v_std(5);

  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
}

TEST(TestsVector, vector_constructor_init) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};

  for (size_t i = 0; i < v_s21.size(); i++) {
    ASSERT_TRUE(v_s21[i] == v_std[i]);
  }
  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
}

TEST(TestsVector, vector_constructor_copy) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  s21::vector<int> v_s21_copy(v_s21);

  for (size_t i = 0; i < v_s21.size(); i++) {
    ASSERT_TRUE(v_s21[i] == v_s21_copy[i]);
  }
  ASSERT_TRUE(v_s21.size() == v_s21_copy.size());
  ASSERT_TRUE(v_s21.capacity() == v_s21_copy.capacity());
}

TEST(TestsVector, vector_constructor_move) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  s21::vector<int> v_s21_move(move(v_s21));

  s21::vector<int> v_std{3, 5, 1, 2};
  s21::vector<int> v_std_move(move(v_std));

  for (size_t i = 0; i < v_s21_move.size(); i++) {
    ASSERT_TRUE(v_s21_move[i] == v_std_move[i]);
  }

  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
  ASSERT_TRUE(v_s21_move.size() == v_std_move.size());
  ASSERT_TRUE(v_s21_move.capacity() == v_std_move.capacity());
}

TEST(TestsVector, vector_operator_eq_move) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  s21::vector<int> v_s21_move;
  v_s21_move = move(v_s21);

  std::vector<int> v_std{3, 5, 1, 2};
  std::vector<int> v_std_move;
  v_std_move = move(v_std);

  for (size_t i = 0; i < v_s21_move.size(); i++) {
    ASSERT_TRUE(v_s21_move[i] == v_std_move[i]);
  }

  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
  ASSERT_TRUE(v_s21_move.size() == v_std_move.size());
  ASSERT_TRUE(v_s21_move.capacity() == v_std_move.capacity());
}

TEST(TestsVector, vector_operator_eq) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  s21::vector<int> v_s21_move;
  v_s21_move = v_s21;

  std::vector<int> v_std{3, 5, 1, 2};
  std::vector<int> v_std_move;
  v_std_move = v_std;

  for (size_t i = 0; i < v_s21_move.size(); i++) {
    ASSERT_TRUE(v_s21_move[i] == v_std_move[i]);
  }

  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
  ASSERT_TRUE(v_s21_move.size() == v_std_move.size());
  ASSERT_TRUE(v_s21_move.capacity() == v_std_move.capacity());
}

TEST(TestsVector, vector_begin) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};

  ASSERT_TRUE(*v_s21.begin() == *v_std.begin());
}

TEST(TestsVector, vector_end) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};

  ASSERT_TRUE(*(v_s21.end() - 1) == *(v_std.end() - 1));
}

TEST(TestsVector, vector_empty) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};

  s21::vector<int> v_s21_empty;
  std::vector<int> v_std_empty;

  ASSERT_TRUE(v_s21.empty() == v_std.empty());
  ASSERT_TRUE(v_s21_empty.empty() == v_std_empty.empty());
}

TEST(TestsVector, vector_size) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};

  s21::vector<int> v_s21_empty;
  std::vector<int> v_std_empty;

  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21_empty.size() == v_std_empty.size());
}

TEST(TestsVector, vector_max_size_int) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};

  s21::vector<int> v_s21_empty;
  std::vector<int> v_std_empty;

  ASSERT_TRUE(v_s21.max_size() == v_std.max_size());
  ASSERT_TRUE(v_s21_empty.max_size() == v_std_empty.max_size());
}

TEST(TestsVector, vector_max_size_double) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};

  s21::vector<int> v_s21_empty;
  std::vector<int> v_std_empty;

  ASSERT_TRUE(v_s21.max_size() == v_std.max_size());
  ASSERT_TRUE(v_s21_empty.max_size() == v_std_empty.max_size());
}

TEST(TestsVector, vector_capacity) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};

  s21::vector<int> v_s21_empty;
  std::vector<int> v_std_empty;

  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
  ASSERT_TRUE(v_s21_empty.capacity() == v_std_empty.capacity());
}

TEST(TestsVector, vector_reserve) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};
  v_s21.reserve(2);
  v_std.reserve(2);
  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());

  v_s21.reserve(20);
  v_std.reserve(20);
  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
}

TEST(TestsVector, vector_shrink_to_fit) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};
  v_s21.reserve(20);
  v_std.reserve(20);
  v_s21.shrink_to_fit();
  v_std.shrink_to_fit();
  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
}

TEST(TestsVector, vector_at) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};

  ASSERT_TRUE(v_s21.at(0) == v_std.at(0));
  ASSERT_TRUE(v_s21.at(1) == v_std.at(1));
  ASSERT_TRUE(v_s21.at(2) == v_std.at(2));
  ASSERT_TRUE(v_s21.at(3) == v_std.at(3));
}

TEST(TestsVector, vector_operator_bracket) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};

  ASSERT_TRUE(v_s21[0] == v_std[0]);
  ASSERT_TRUE(v_s21[1] == v_std[1]);
  ASSERT_TRUE(v_s21[2] == v_std[2]);
  ASSERT_TRUE(v_s21[3] == v_std[3]);
}

TEST(TestsVector, vector_front) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};

  ASSERT_TRUE(v_s21.front() == v_std.front());
}

TEST(TestsVector, vector_back) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};

  ASSERT_TRUE(v_s21.back() == v_std.back());
}

TEST(TestsVector, vector_data) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};

  ASSERT_TRUE(*v_s21.data() == *v_std.data());
}

TEST(TestsVector, vector_clear) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};
  v_s21.clear();
  v_std.clear();
  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
}

TEST(TestsVector, vector_erase) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};
  v_s21.erase(v_s21.begin());
  v_std.erase(v_std.begin());
  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
  for (size_t i = 0; i < v_s21.size(); i++) {
    ASSERT_TRUE(v_s21[i] == v_std[i]);
  }
}

TEST(TestsVector, vector_push_back) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};
  v_s21.push_back(8);
  v_std.push_back(8);
  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
  for (size_t i = 0; i < v_s21.size(); i++) {
    ASSERT_TRUE(v_s21[i] == v_std[i]);
  }
}

TEST(TestsVector, vector_pop_back) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};
  v_s21.pop_back();
  v_std.pop_back();
  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
  for (size_t i = 0; i < v_s21.size(); i++) {
    ASSERT_TRUE(v_s21[i] == v_std[i]);
  }
}

TEST(TestsVector, vector_swap) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};
  s21::vector<int> v_s21_swap{8, 8, 8};
  std::vector<int> v_std_swap{8, 8, 8};
  v_s21_swap.swap(v_s21);
  v_std_swap.swap(v_std);
  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21_swap.size() == v_std_swap.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
  ASSERT_TRUE(v_s21_swap.capacity() == v_std_swap.capacity());
  for (size_t i = 0; i < v_s21.size(); i++) {
    ASSERT_TRUE(v_s21[i] == v_std[i]);
  }
  for (size_t i = 0; i < v_s21_swap.size(); i++) {
    ASSERT_TRUE(v_s21_swap[i] == v_std_swap[i]);
  }
}

TEST(TestsVector, vector_iterator) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};
  v_s21.insert(v_s21.begin(), 69);
  v_std.insert(v_std.begin(), 69);
  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
  for (size_t i = 0; i < v_s21.size(); i++) {
    ASSERT_TRUE(v_s21[i] == v_std[i]);
  }
}

TEST(TestsVector, vector_emplace) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};
  const int *a = &v_s21[1];
  v_s21.emplace(a, 69);
  v_std.emplace(++v_std.begin(), 69);
  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
  for (size_t i = 0; i < v_s21.size(); i++) {
    ASSERT_TRUE(v_s21[i] == v_std[i]);
  }
}

TEST(TestsVector, vector_emplace_back) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  std::vector<int> v_std{3, 5, 1, 2};
  v_s21.emplace_back(69);
  v_std.emplace_back(69);
  ASSERT_TRUE(v_s21.size() == v_std.size());
  ASSERT_TRUE(v_s21.capacity() == v_std.capacity());
  for (size_t i = 0; i < v_s21.size(); i++) {
    ASSERT_TRUE(v_s21[i] == v_std[i]);
  }
}

TEST(TestsVector, vector_thr_ex) {
  s21::vector<int> v_s21{3, 5, 1, 2};
  int check = 0;
  try {
    v_s21.at(10);
  } catch (const std::exception &e) {
    check = 1;
  }
  ASSERT_TRUE(check == 1);
}