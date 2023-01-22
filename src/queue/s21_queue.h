#ifndef SRC_S21_QUEUE_H
#define SRC_S21_QUEUE_H

#include <initializer_list>

#include "../list/s21_list.h"

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  queue() { queue_ = new s21::list<T>; }

  queue(std::initializer_list<T> const &items) {
    queue_ = new s21::list<T>(items);
  }

  queue(const queue &q) { queue_ = new s21::list<T>(*q.queue_); }
  queue(queue &&q) : queue() { *queue_ = std::move(*q.queue_); }
  ~queue() { delete queue_; }

  queue<T> &operator=(queue &&q) {
    if (*this != q) {
      queue_->clear();
      *queue_ = std::move(*q.queue_);
    }
    return *this;
  }

  const_reference front() const { return queue_->front(); }
  const_reference back() const { return queue_->back(); }

  bool empty() { return queue_->empty(); }
  size_type size() const { return queue_->size(); }

  void push(const_reference value) { queue_->push_back(value); }
  void pop() { queue_->pop_front(); }
  void swap(queue &other) { queue_->swap(*other.queue_); }

  bool operator!=(queue &other) const { return !(*queue_ == *other.queue_); }

  template <typename... Args>
  void emplace_back(Args &&...args) {
    queue_->emplace_back(std::forward<Args>(args)...);
  }

 private:
  s21::list<T> *queue_;
};
}  // namespace s21

#endif  //  SRC_S21_QUEUE_H
