#ifndef SRC_S21_SET_ITERATOR_H
#define SRC_S21_SET_ITERATOR_H

#include <cstddef>
#include <iostream>

namespace s21 {
template <typename Key>
class NodeSet {
 public:
  NodeSet *parent;
  NodeSet *left;
  NodeSet *right;
  Key data;  // const

  NodeSet(const Key &value = Key(), NodeSet *p = NULL, NodeSet *l = NULL,
          NodeSet *r = NULL) {
    data = value;
    parent = p;
    left = l;
    right = r;
  }

  ~NodeSet() {}

  NodeSet *next() {
    NodeSet *next = this;
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

  NodeSet *prev() {
    NodeSet *prev = this;
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

  void free_node(NodeSet *tree) {
    if (tree->left) free_node(tree->left);
    if (tree->right) free_node(tree->right);
    delete tree;
  }

  NodeSet *copy_node(NodeSet *root) {
    NodeSet *node = root;
    if (node) {
      node = new NodeSet(root->data);
      node->left = copy_node(root->left);
      node->right = copy_node(root->right);
    }
    return node;
  }
};

template <typename Key>
class SetIterator {
 public:
  using key_type = Key;
  using value_type = const key_type;
  using reference = value_type &;

  NodeSet<Key> *it;

  SetIterator(NodeSet<Key> *root = NULL) : it(root) {}
  SetIterator(const SetIterator &other) { *this = other; }
  ~SetIterator() {}

  SetIterator &operator=(const SetIterator &other) {
    it = other.it;
    return *this;
  }

  reference operator*() { return it->data; }

  SetIterator &operator++() {
    it = it->next();
    return *this;
  }

  SetIterator operator++(int) {  // for me
    SetIterator buffer(*this);
    it = it->next();
    return buffer;
  }

  SetIterator &operator--() {
    it = it->prev();
    return *this;
  }

  SetIterator operator--(int) {  //  for me
    SetIterator buffer(*this);
    it = it->prev();
    return buffer;
  }

  bool operator==(const SetIterator &other) const { return it == other.it; }

  bool operator!=(const SetIterator &other) const { return it != other.it; }
};

template <typename Key>
class SetConstIterator {
 public:
  using key_type = Key;
  using value_type = const key_type;
  using const_reference = const value_type &;

  SetConstIterator(NodeSet<Key> *root = NULL) : it(root) {}
  SetConstIterator(const SetConstIterator &other) { *this = other; }
  ~SetConstIterator() {}

  const_reference operator*() const { return it->data; }

  SetConstIterator &operator++() {
    it = it->next();
    return *this;
  }

  SetConstIterator operator++(int value) {  // for me
    SetConstIterator buffer(*this);
    it = it->next();
    return buffer;
  }

  SetConstIterator &operator--() {
    it = it->prev();
    return *this;
  }

  SetConstIterator operator--(int value) {  //  for me
    SetConstIterator buffer(*this);
    it = it->prev();
    return buffer;
  }

  bool operator==(const SetConstIterator &other) const {
    return it == other.it;
  }

  bool operator!=(const SetConstIterator &other) const {
    return it != other.it;
  }

  NodeSet<Key> *getNode() { return it; }

 private:
  NodeSet<Key> *it;
};

}  //  namespace s21
#endif  //  SRC_S21_SET_ITERATOR_H
