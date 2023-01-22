#include <gtest/gtest.h>

#include "s21_array_tests.cc"
#include "s21_list_tests.cc"
#include "s21_map_tests.cc"
#include "s21_multiset_tests.cc"
#include "s21_queue_tests.cc"
#include "s21_set_tests.cc"
#include "s21_stack_tests.cc"
#include "s21_vector_tests.cc"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
