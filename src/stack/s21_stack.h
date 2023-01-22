#ifndef SRC_S21_STACK_H
#define SRC_S21_STACK_H

#include <initializer_list>
#include <iostream>
#include <stack>

#include "../list/s21_list.h"

namespace s21 {
template <typename T>
class stack {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  stack() { stack_ = new list<T>; }
  stack(std::initializer_list<value_type> const &items) {
    stack_ = new list<T>(items);
  }
  stack(const stack &s) { stack_ = new list<T>(*s.stack_); }
  stack(stack &&s) : stack() { *stack_ = std::move(*s.stack_); }
  ~stack() {
    if (stack_) delete stack_;
  }
  stack<T> &operator=(stack &&s) {
    if (*this != s) {
      stack_->clear();
      *stack_ = std::move(*s.stack_);
    }
    return *this;
  }
  const_reference top() { return stack_->back(); }
  bool empty() { return stack_->empty(); }
  size_type size() { return stack_->size(); }
  void push(const_reference value) { stack_->push_back(value); }
  void pop() { stack_->pop_back(); }
  void swap(stack &other) { stack_->swap(*other.stack_); }
  bool operator!=(stack &other) const { return *stack_ != *other.stack_; }
  bool operator==(stack &other) const { return *stack_ == *other.stack_; }
  template <typename... Args>
  void emplace_front(Args &&...args) {
    this->stack_->emplace_back(std::forward<Args>(args)...);
  }

 private:
  list<T> *stack_;
};
}  // namespace s21

#endif