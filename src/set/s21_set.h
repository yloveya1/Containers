#ifndef S21_SET_H
#define S21_SET_H

#include <cmath>
#include <iostream>
#include <utility>

#include "../vector/s21_vector.h"
#include "./s21_set_iterator.h"

namespace s21 {
//  ___________________________SET_CLASS________________________________________
template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = const key_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = SetIterator<Key>;
  using const_iterator = SetConstIterator<Key>;
  using size_type = std::size_t;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &m);
  set(set &&m) : set() { *this = std::move(m); }
  ~set();
  set &operator=(set &&m);
  set &operator=(const set &m);

  iterator begin() const { return SetIterator<Key>(head_->parent); }
  iterator end() const { return SetIterator<Key>(tail_); }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const;

  void clear();
  virtual std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const Key &key) const { return find_by_key(key).first; }
  bool contains(const Key &key) const { return find_by_key(key).second; }

  template <class... Args>
  vector<std::pair<SetIterator<Key>, bool>> emplace(Args &&...args);

 protected:
  NodeSet<Key> *root_;
  NodeSet<Key> *head_;
  NodeSet<Key> *tail_;
  size_type size_;

  void connect_node(NodeSet<Key> *parent, NodeSet<Key> **childptr,
                    NodeSet<Key> *child);
  std::pair<iterator, bool> find_by_key(const key_type &key) const;
  void rebuild_node(iterator pos, NodeSet<Key> *child);
  virtual bool insertCompare(const Key &value, NodeSet<Key> *parent) {
    return value < parent->data;
  }
};  //  class set

//  _________________________SET_METHODS________________________________________
template <typename Key>
set<Key>::set() {
  root_ = NULL;
  head_ = new NodeSet<Key>();
  tail_ = new NodeSet<Key>();
  head_->parent = tail_;
  tail_->parent = head_;
  size_ = 0;
}

template <typename Key>
set<Key>::set(std::initializer_list<const Key> const &items) : set() {
  for (auto key : items) {
    insert(key);
  }
}

template <typename Key>
set<Key>::set(const set<Key> &m) {
  root_ = NULL;
  head_ = NULL;
  tail_ = NULL;
  *this = m;
}

template <typename Key>
set<Key>::~set() {
  if (root_ || head_ || tail_) {
    clear();
  }
}

template <typename Key>
set<Key> &set<Key>::operator=(set &&m) {
  clear();
  root_ = m.root_;
  head_ = m.head_;
  tail_ = m.tail_;
  size_ = m.size_;
  m.root_ = NULL;
  m.head_ = NULL;
  m.tail_ = NULL;
  m.size_ = 0;
  return *this;
}

template <typename Key>
set<Key> &set<Key>::operator=(const set &m) {
  clear();
  root_ = root_->copy_node(m.root_);
  head_ = m.head_;
  tail_ = m.tail_;
  size_ = m.size_;
  return *this;
}

template <typename Key>
std::size_t set<Key>::max_size() const {
  std::allocator<int> alloc;
  return alloc.max_size() / 10;
}

template <typename Key>
void set<Key>::clear() {
  if (root_) {
    root_->free_node(root_);
    root_ = NULL;
    head_ = NULL;
    tail_ = NULL;
  }
  if (head_) {
    head_->free_node(head_);
    head_ = NULL;
  }
  if (tail_) {
    tail_->free_node(tail_);
    tail_ = NULL;
  }
  size_ = 0;
}

template <typename Key>
std::pair<SetIterator<Key>, bool> set<Key>::insert(const Key &value) {
  if (empty()) {
    root_ = new NodeSet<Key>(value);
    connect_node(root_, &root_->left, head_);
    connect_node(root_, &root_->right, tail_);
    size_++;
    return std::pair<SetIterator<Key>, bool>(SetIterator<Key>(root_), true);
  }

  NodeSet<Key> *it = root_;
  NodeSet<Key> *parent = NULL;
  while (it && it != head_ && it != tail_) {
    parent = it;
    if (this->insertCompare(value, parent)) {
      it = it->left;
    } else if (value > it->data) {
      it = it->right;
    } else {
      return std::pair<SetIterator<Key>, bool>(SetIterator<Key>(it), false);
    }
  }

  NodeSet<Key> *result = new NodeSet<Key>(value, parent);

  if (this->insertCompare(value, parent)) {
    connect_node(parent, &parent->left, result);
    connect_node(result, &result->left, it);

  } else if (value > parent->data) {
    connect_node(parent, &parent->right, result);
    connect_node(result, &result->right, it);
  }
  size_++;
  return std::pair<SetIterator<Key>, bool>(SetIterator<Key>(result), true);
}

template <typename Key>
void set<Key>::erase(SetIterator<Key> pos) {
  if (empty()) {
    return;
  }

  bool left_child = (pos.it->left) ? true : false;
  bool right_child = (pos.it->right) ? true : false;

  if (!left_child && !right_child) {  //  является листом
    rebuild_node(pos, NULL);
    delete pos.it;
  } else if (!left_child ||
             !right_child) {  //  только одно поддерево второго ребенка нет
    rebuild_node(pos, (right_child) ? pos.it->right : pos.it->left);
    delete pos.it;
  } else {
    SetIterator<Key> next = pos;
    ++next;
    if (!next.it->left &&
        !next.it->right) {  //  самый левый из правого поддерева лист
      rebuild_node(next, NULL);
    } else {
      rebuild_node(next,
                   next.it->right);  //  самый левый из правого поддерева
                                     //  имеет одного ребенка
    }
    pos.it->data = next.it->data;
    delete next.it;
  }
  size_--;
}

template <typename Key>
void set<Key>::swap(set<Key> &other) {
  set<Key> buffer(other);
  other = *this;
  *this = buffer;
}

template <typename Key>
void set<Key>::merge(set<Key> &other) {
  auto it = other.begin();
  for (; it != other.end(); it++) {
    insert(it.it->data);
  }
}

// PROTECTED_METHODS
template <typename Key>
void set<Key>::connect_node(NodeSet<Key> *parent, NodeSet<Key> **childptr,
                            NodeSet<Key> *child) {
  if (child) {
    child->parent = parent;
  }

  *childptr = child;
}

template <typename Key>
std::pair<SetIterator<Key>, bool> set<Key>::find_by_key(
    const key_type &key) const {
  if (empty()) {
    return std::pair<iterator, bool>(end(), false);
  }
  NodeSet<Key> *it = root_;
  while (it && it != head_ && it != tail_) {
    if (key < it->data) {
      it = it->left;
    } else if (key > it->data) {
      it = it->right;
    } else {
      return std::pair<iterator, bool>(it, true);
    }
  }
  return std::pair<iterator, bool>(end(), false);
}

template <typename Key>
void set<Key>::rebuild_node(iterator pos, NodeSet<Key> *child) {
  if (pos.it->parent->left == pos.it) {
    pos.it->parent->left = child;
  } else {
    pos.it->parent->right = child;
  }

  if (child) {
    child->parent = pos.it->parent;
  }
}

template <typename Key>
template <class... Args>
vector<std::pair<SetIterator<Key>, bool>> set<Key>::emplace(Args &&...args) {
  vector<std::pair<iterator, bool>> result;
  vector<key_type> argsVector{args...};
  for (auto &i : argsVector) {
    result.push_back(insert(i));
  }
  return result;
}

}  // namespace s21

#endif
