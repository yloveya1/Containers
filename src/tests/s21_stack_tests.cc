#include <gmock/gmock.h>

#include <iostream>
#include <stack>

#include "../stack/s21_stack.h"

TEST(Stack, stack_top) {
  s21::stack<int> check;
  s21::stack<int> q;

  for (int i = 0; i < 50; i++) {
    check.push(i);
    q.push(i);

    if (i % 3 == 0) {
      check.pop();
      q.pop();
    }
  }
  ASSERT_TRUE((q == check) == true);
  ASSERT_TRUE(q.top() == check.top());
  ASSERT_TRUE(q.size() == check.size());
}

TEST(Stack, stack_empty) {
  stack<int> check;
  s21::stack<int> q;
  ASSERT_TRUE(check.empty() == q.empty());
  check.push(1);
  q.push(1);
  ASSERT_TRUE(check.empty() == q.empty());
}

TEST(Stack, stack_swap) {
  s21::stack<int> check;
  s21::stack<int> buffer;
  s21::stack<int> q;

  for (int i = 0; i < 50; i++) {
    buffer.push(i);
    check.push(i);

    if (i % 3 == 0) {
      buffer.pop();
      check.pop();
    }
  }

  for (int i = 50; i < 150; i++) {
    q.push(i);

    if (i % 3 == 0) {
      q.pop();
    }
  }
  q.swap(buffer);
  ASSERT_TRUE(q.top() == check.top());
  ASSERT_TRUE(q.size() == check.size());
  ASSERT_TRUE((q != check) == false);
}

TEST(Stack, stack_move) {
  s21::stack<int> check = {1, 5, 9, 15};
  s21::stack<int> buffer = {15, 18, 23};
  s21::stack<int> q = {1, 5, 9, 15};
  buffer = move(check);
  ASSERT_TRUE(check.size() == 0);
  ASSERT_TRUE((buffer == q) == true);
}

TEST(Stack, stack_constructors) {
  s21::stack<int> check;
  check.push(3);
  check.push(1);
  s21::stack<int> buffer = {3, 1};
  s21::stack<int> q = move(buffer);
  s21::stack<int> d(q);
  ASSERT_TRUE(buffer.size() == 0);
  ASSERT_TRUE((check == q) == true);
  ASSERT_TRUE((check == d) == true);
  ASSERT_TRUE((q == d) == true);
}

TEST(Stack, stack_emplace) {
  s21::stack<int> a = {1, 2, 3, 4, 5};
  s21::stack<int> b = {1, 2, 3, 4, 5, 6};
  a.emplace_front(6);
  ASSERT_TRUE(a == b);
}