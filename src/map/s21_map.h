#ifndef SRC_S21_MAP_H
#define SRC_S21_MAP_H

#include <initializer_list>
#include <utility>

#include "../vector/s21_vector.h"
#include "s21_map_iterator.h"

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MapIterator<Key, T>;
  using const_iterator = MapConstIterator<Key, T>;
  using size_type = std::size_t;

  map() {
    root_ = NULL;
    head_ = new Node_map<Key, T>();
    tail_ = new Node_map<Key, T>();
    head_->parent = tail_;
    tail_->parent = head_;
    size_ = 0;
  }

  map(std::initializer_list<value_type> const &items) : map() {
    for (auto pair : items) {
      insert(pair);
    }
  }

  map(const map &m) {
    root_ = NULL;
    head_ = NULL;
    tail_ = NULL;
    *this = m;
  }

  map(map &&m) : map() { *this = std::move(m); }

  ~map() {
    if (root_ || head_ || tail_) {
      clear();
    }
  }

  map &operator=(map &&m) {
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

  map &operator=(const map &m) {
    clear();
    root_ = root_->copy_node(m.root_);
    head_ = m.head_;
    tail_ = m.tail_;
    size_ = m.size_;
    return *this;
  }

  mapped_type &at(const Key &key) const {
    const auto buffer = find_by_key(key);
    if (buffer.second == false) {
      throw std::out_of_range("Key not found");
    }
    return buffer.first.it->data.second;
  }

  mapped_type &operator[](const Key &key) {
    auto buffer = find_by_key(key);
    iterator it = buffer.first;
    if (buffer.second == false) {
      it = insert(value_type(key, T())).first;
    }
    return it.it->data.second;
  }

  iterator begin() const { return iterator(head_->parent); }
  iterator end() const { return iterator(tail_); }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }

  size_type max_size() const {
    std::allocator<std::pair<const Key, T>> alloc;
    return alloc.max_size() / 5;
  }

  void clear() {
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

  std::pair<iterator, bool> insert(const value_type &value) {
    if (empty()) {
      root_ = new Node_map<Key, T>(value);
      connect_node(root_, &root_->left, head_);
      connect_node(root_, &root_->right, tail_);
      size_++;
      return std::pair<iterator, bool>(iterator(root_), true);
    }

    Node_map<Key, T> *it = root_;
    Node_map<Key, T> *parent = NULL;
    while (it && it != head_ && it != tail_) {
      parent = it;
      if (value.first < it->data.first) {
        it = it->left;
      } else if (value.first > it->data.first) {
        it = it->right;
      } else {
        return std::pair<iterator, bool>(iterator(it), false);
      }
    }

    Node_map<Key, T> *result = new Node_map<Key, T>(value, parent);

    if (value.first < parent->data.first) {
      connect_node(parent, &parent->left, result);
      connect_node(result, &result->left, it);

    } else if (value.first > parent->data.first) {
      connect_node(parent, &parent->right, result);
      connect_node(result, &result->right, it);
    }
    size_++;
    return std::pair<iterator, bool>(iterator(result), true);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return insert(value_type(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    auto reuslt = insert(value_type(key, obj));
    if (reuslt.second == false) {
      reuslt.first.it->data.second = obj;
    }
    return reuslt;
  }

  void erase(iterator pos) {
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
      MapIterator<Key, T> next = pos;
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

  void swap(map &other) {
    std::swap(this->root_, other.root_);
    std::swap(this->head_, other.head_);
    std::swap(this->tail_, other.tail_);
    std::swap(this->size_, other.size_);
  }

  void merge(map &other) {
    auto it = other.begin();
    for (; it != other.end(); it++) {
      insert(it.it->data);
    }
  }

  bool contains(const Key &key) const { return find_by_key(key).second; }

  template <class... Args>
  vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    vector<std::pair<iterator, bool>> result;
    vector<std::pair<Key, T>> argsVector{args...};
    for (auto &i : argsVector) {
      result.push_back(insert(i));
    }
    return result;
  }

 private:
  Node_map<Key, T> *root_;
  Node_map<Key, T> *head_;
  Node_map<Key, T> *tail_;
  size_type size_;

  void connect_node(Node_map<Key, T> *parent, Node_map<Key, T> **childptr,
                    Node_map<Key, T> *child) {
    if (child) {
      child->parent = parent;
    }
    *childptr = child;
  }

  std::pair<iterator, bool> find_by_key(const key_type &key) const {
    if (empty()) {
      return std::pair<iterator, bool>(end(), false);
    }
    Node_map<Key, T> *it = root_;
    while (it && it != head_ && it != tail_) {
      if (key < it->data.first) {
        it = it->left;
      } else if (key > it->data.first) {
        it = it->right;
      } else {
        return std::pair<iterator, bool>(it, true);
      }
    }
    return std::pair<iterator, bool>(end(), false);
  }

  void rebuild_node(iterator pos, Node_map<Key, T> *child) {
    if (pos.it->parent->left == pos.it) {
      pos.it->parent->left = child;
    } else {
      pos.it->parent->right = child;
    }

    if (child) {
      child->parent = pos.it->parent;
    }
  }
};
}  // namespace s21

#endif  //  SRC_S21_MAP_H
