#include <gmock/gmock.h>

#include <queue>

#include "../queue/s21_queue.h"

using namespace std;

TEST(Queue, queue_front) {
  queue<int> check;
  s21::queue<int> q;

  for (int i = 0; i < 50; i++) {
    check.push(i);
    q.push(i);

    if (i % 3 == 0) {
      check.pop();
      q.pop();
    }
  }

  ASSERT_TRUE(check.front() == q.front());
  ASSERT_TRUE(q.size() == check.size());
}

TEST(Queue, queue_back) {
  queue<int> check;
  s21::queue<int> q;

  for (int i = 0; i < 50; i++) {
    check.push(i);
    q.push(i);

    if (i % 3 == 0) {
      check.pop();
      q.pop();
    }
  }

  ASSERT_TRUE(check.back() == q.back());
  ASSERT_TRUE(q.size() == check.size());
}

TEST(Queue, queue_swap) {
  s21::queue<int> check;
  s21::queue<int> buffer;
  s21::queue<int> q;

  for (int i = 0; i < 50; i++) {
    buffer.push(i);
    check.push(i);

    if (i % 3 == 0) {
      buffer.pop();
      check.pop();
    }
  }

  for (int i = 50; i < 70; i++) {
    q.push(i);

    if (i % 3 == 0) {
      q.pop();
    }
  }

  q.swap(buffer);

  ASSERT_TRUE(q.back() == check.back());
  ASSERT_TRUE(q.size() == check.size());
  ASSERT_TRUE(q.front() == check.front());
  ASSERT_TRUE((q != check) == false);
}

TEST(Queue, queue_not_empty) {
  s21::queue<int> q;

  for (int i = 0; i < 50; i++) {
    q.push(i);

    if (i % 3 == 0) {
      q.pop();
    }
  }
  ASSERT_TRUE(q.empty() == false);
}

TEST(Queue, queue_empty) {
  s21::queue<int> q;
  ASSERT_TRUE(q.empty() == true);
}

TEST(Queue, queue_operator_not_eq) {
  s21::queue<int> buffer;
  s21::queue<int> q;
  s21::queue<int> q2;

  for (int i = 0; i < 50; i++) {
    buffer.push(i);
    q2.push(i);

    if (i % 3 == 0) {
      buffer.pop();
      q2.pop();
    }
  }

  for (int i = 50; i < 70; i++) {
    q.push(i);

    if (i % 3 == 0) {
      q.pop();
    }
  }

  ASSERT_TRUE((q != buffer) == true);
  ASSERT_TRUE((q2 != buffer) == false);
}

TEST(Queue, queue_operator_eq) {
  s21::queue<int> q;
  s21::queue<int> buffer;

  for (int i = 0; i < 50; i++) {
    buffer.push(i);
    q.push(i);

    if (i % 3 == 0) {
      buffer.pop();
    }
  }

  s21::queue<int> check(buffer);
  q = move(buffer);

  ASSERT_TRUE(q.front() == check.front());
  ASSERT_TRUE(q.back() == check.back());
  ASSERT_TRUE(q.size() == check.size());
  ASSERT_TRUE((q != check) == false);
}

TEST(Queue, queue_constructor_init_list) {
  s21::queue<int> q{3, 5, 2, 1, 6};
  s21::queue<int> check;
  check.push(3);
  check.push(5);
  check.push(2);
  check.push(1);
  check.push(6);

  ASSERT_TRUE((q != check) == false);
}

TEST(Queue, queue_constructor_move) {
  s21::queue<int> q{3, 5, 2, 1, 6};
  s21::queue<int> check(move(q));

  ASSERT_TRUE((q != check) == true);
  ASSERT_TRUE(q.size() == 0);
}

TEST(Queue, queue_emplace) {
  s21::queue<int> q{3, 5, 2, 1, 6};
  q.emplace_back(7);

  ASSERT_TRUE(q.back() == 7);
}