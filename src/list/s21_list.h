#ifndef SRC_S21_LIST_H
#define SRC_S21_LIST_H

#include <initializer_list>
#include <iostream>

#include "list_const_iterator.h"
#include "list_iterator.h"
#include "node.h"

using namespace std;
namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using node_allocator = typename std::allocator_traits<
      std::allocator<T>>::template rebind_alloc<Node<T>>;
  node_allocator allocator;
  // List functions
  list() : size_(0) { init(); }

  explicit list(size_type n) : list() {
    while (n--) {
      this->push_back(value_type());
    }
  }

  list(std::initializer_list<value_type> const &items) : list() {
    for (auto nodes : items) {
      this->push_back(nodes);
    }
  }

  list(const list &l) : list() {
    for (auto &nodes : l) {
      push_back(nodes);
    }
  }

  list(list &&l) : list(0) { *this = move(l); }

  ~list() { clear(); }

  list<T> &operator=(list &l) noexcept {
    list<T>(l).swap(*this);
    return *this;
  }

  list<T> &operator=(list &&l) noexcept {
    this->clear();
    l.swap(*this);
    return *this;
  }

  // List element access
  const_reference front() const { return head->data; }
  const_reference back() const { return end_->prev->data; }

  // List iterators
  iterator begin() const { return iterator(head); }
  iterator end() const { return iterator(end_); }

  const_iterator cbegin() const { return const_iterator(head); }
  const_iterator cend() const { return const_iterator(end_); }

  // List Capacity
  bool empty() const { return this->size() == 0; }
  size_type size() const { return this->size_; }
  size_type max_size() const { return allocator.max_size(); }

  // list modifiers
  void clear() {
    while (head) {
      pop_front();
    }
    if (end_) delete end_;
  }
  iterator insert(iterator pos, const_reference value) {
    iterator res;
    if (size_ == 0) {
      if (!head) {
        init();
      }
      head->data = value;
      res = this->begin();
    } else if (pos == this->begin()) {
      head = head->prev = new Node<T>(value, head, end_);
      end_->pnext = head;
      res = this->begin();
    } else {
      pos->prev->pnext = new Node<T>(value, pos.getNode(), pos->prev);
      res = pos->prev->pnext;
      pos->prev = res.getNode();
    }
    size_++;
    return res;
  }

  void erase(iterator pos) {
    if (pos == end()) {
      return;
    }
    if (head->pnext != end_) {
      if (pos == this->begin()) {
        pos->pnext->prev = end_;
        head = pos->pnext;
        end_->pnext = head;
      } else {
        pos->prev->pnext = pos->pnext;
        pos->pnext->prev = pos->prev;
      }
      size_--;
      delete pos.getNode();
    } else {
      delete head;
      delete end_;
      this->head = this->end_ = nullptr;
      size_ = 0;
    }
  }

  void push_back(const_reference value) { insert(this->end(), value); }

  void pop_back() { erase(--this->end()); }

  void push_front(const_reference value) { insert(this->begin(), value); }

  void pop_front() { erase(this->begin()); }

  void swap(list &other) {
    std::swap(this->head, other.head);
    std::swap(this->end_, other.end_);
    std::swap(this->size_, other.size_);
  }

  void merge(list &other) {
    iterator this_it = this->begin(), other_it = other.begin();
    if (!other.empty()) {
      while (this_it != end_) {
        while (*this_it > *other_it && other_it != other.end_) {
          this->insert(this_it, *other_it);
          ++other_it;
        }
        ++this_it;
      }
      while (other_it != other.end()) {
        this->insert(this->end(), *other_it);
        ++other_it;
      }
    }
    other.clear();
  }

  void splice(const_iterator pos, list &other) {
    if (!other.empty()) {
      if (this->empty()) {
        pos = end_;
        delete begin().getNode();
      }
      if (pos.getNode() == head || this->empty()) {
        head = other.head;
      } else {
        pos->prev->pnext = other.head;
        other.head->prev = pos->prev;
      }
      other.end_->prev->pnext = pos.getNode();
      pos->prev = other.end_->prev;

      other.head = nullptr;
      size_ += other.size_;
      other.size_ = 0;
    }
  }

  void reverse() {
    iterator it = this->begin();
    int count = size_ + 1;
    while (count--) {
      std::swap(it.getNode()->pnext, it.getNode()->prev);
      ++it;
    }
    head = end_->pnext;
  }

  void unique() {
    iterator it = this->begin(), temp = it->pnext;
    while (!this->empty() && it->pnext != end_) {
      while (it.getNode()->data == temp.getNode()->data) {
        ++temp;
        erase(it->pnext);
      }
      ++it, ++temp;
    }
  }
  void sort() {
    if (size_ <= 1) {
      return;
    }
    list<T> first;
    list<T> second;
    size_t counter = 0;
    for (auto i : *this) {
      if (counter < size_ / 2) {
        first.push_back(i);
      } else {
        second.push_back(i);
      }
      counter++;
    }
    first.sort();
    second.sort();
    first.merge(second);
    this->swap(first);
  }

  // functions for me
  // void Print_list() {
  //     if (size_) {
  //         for (const auto &node : *this) {
  //             cout << node << endl;
  //         }
  //     }
  // }
  bool operator==(const list &other) {
    bool check = true;
    if (size_ != other.size_) return false;
    const_iterator it = cbegin(), ot_it = other.cbegin();
    for (; it != cend() && ot_it != other.cend() && check; ++it, ++ot_it) {
      if (*it != *ot_it) {
        check = false;
      }
    }
    return check;
  }

  bool operator!=(const list &other) { return !(*this == other); }

  void init() {
    head = new Node<T>(value_type());
    end_ = new Node<T>(value_type(), head, head);
    head->prev = end_;
    head->pnext = end_;
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    iterator it(pos.getNode());
    return this->insert(it, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void emplace_back(Args &&...args) {
    this->push_back(value_type(std::forward<Args>(args)...));
  }

  template <typename... Args>
  void emplace_front(Args &&...args) {
    this->push_front(value_type(std::forward<Args>(args)...));
  }

 private:
  Node<T> *head;
  Node<T> *end_;
  size_type size_;
};

}  // namespace s21

#endif  // SRC_S21_LIST_H