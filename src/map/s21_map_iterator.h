#ifndef SRC_S21_MAP_ITERATOR_H
#define SRC_S21_MAP_ITERATOR_H

#include <cstddef>
#include <utility>

template <typename Key, typename T>
class Node_map {
 public:
  Node_map *parent;
  Node_map *left;
  Node_map *right;
  std::pair<Key, T> data;

  Node_map(const std::pair<const Key, T> &value = std::pair<const Key, T>(),
           Node_map *p = NULL, Node_map *l = NULL, Node_map *r = NULL) {
    data = value;
    parent = p;
    left = l;
    right = r;
  }

  ~Node_map() {}

  Node_map *next() {
    Node_map *next = this;
    if (next->right) {
      next = next->right;
      while (next->left) {
        next = next->left;
      }
    } else {
      while (next->parent && next->parent->right == next) {
        next = next->parent;
      }
      next = next->parent;
    }
    return next;
  }

  Node_map *prev() {
    Node_map *prev = this;
    if (prev->left) {
      prev = prev->left;
      while (prev->right) {
        prev = prev->right;
      }
    } else {
      while (prev->parent && prev->parent->left == prev) {
        prev = prev->parent;
      }
      prev = prev->parent;
    }
    return prev;
  }

  void free_node(Node_map *tree) {
    if (tree->left) free_node(tree->left);
    if (tree->right) free_node(tree->right);
    delete tree;
  }

  Node_map *copy_node(Node_map *root) const {
    Node_map *node = root;
    if (node) {
      node = new Node_map(root->data);
      node->left = copy_node(root->left);
      node->right = copy_node(root->right);
    }
    return node;
  }
};

template <typename Key, typename T>
class MapIterator {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;

  Node_map<Key, T> *it;

  MapIterator(Node_map<Key, T> *root = NULL) : it(root) {}
  MapIterator(const MapIterator &other) { *this = other; }
  ~MapIterator() {}

  MapIterator &operator=(const MapIterator &other) {
    it = other.it;
    return *this;
  }

  reference operator*() { return it->data; }

  MapIterator &operator++() {
    it = it->next();
    return *this;
  }

  MapIterator operator++(int) {  // for me
    MapIterator buffer(*this);
    it = it->next();
    return buffer;
  }

  MapIterator &operator--() {
    it = it->prev();
    return *this;
  }

  MapIterator operator--(int) {  //  for me
    MapIterator buffer(*this);
    it = it->prev();
    return buffer;
  }

  bool operator==(const MapIterator &other) const { return it == other.it; }

  bool operator!=(const MapIterator &other) const { return it != other.it; }
};

template <typename Key, typename T>
class MapConstIterator {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using const_reference = const value_type &;

  MapConstIterator(Node_map<Key, T> *root = NULL) : it_(root) {}
  MapConstIterator(const MapConstIterator &other) { *this = other; }
  MapConstIterator(const MapIterator<Key, T> &other) : it_(other.it) {}
  ~MapConstIterator() {}

  const_reference operator*() const { return it_->data; }

  MapConstIterator &operator++() {
    it_ = it_->next();
    return *this;
  }

  MapConstIterator operator++(int value) {  // for me
    MapConstIterator buffer(*this);
    it_ = it_->next();
    return buffer;
  }

  MapConstIterator &operator--() {
    it_ = it_->prev();
    return *this;
  }

  MapConstIterator operator--(int value) {  //  for me
    MapConstIterator buffer(*this);
    it_ = it_->prev();
    return buffer;
  }

  bool operator==(const MapConstIterator &other) const {
    return it_ == other.it_;
  }

  bool operator!=(const MapConstIterator &other) const {
    return it_ != other.it_;
  }

  Node_map<Key, T> *getNode() { return it_; }

 private:
  Node_map<Key, T> *it_;
};

#endif  //  SRC_S21_MAP_ITERATOR_H
