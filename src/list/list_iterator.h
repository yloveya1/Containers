#ifndef SRC_LIST_ITERATOR_H__
#define SRC_LIST_ITERATOR_H__
#include "node.h"

namespace s21 {
template <typename T>
class ListIterator {
  using reference = T &;

 public:
  ListIterator(){};
  ListIterator(Node<T> *node) : _currentNode(node) {}
  ListIterator<T> &operator--() {
    _currentNode = _currentNode->prev;
    return *this;
  }
  ListIterator<T> &operator++() {
    _currentNode = _currentNode->pnext;
    return *this;
  }
  reference operator*() { return _currentNode->data; }
  bool operator!=(const ListIterator<T> &it) const {
    return _currentNode != it._currentNode;
  }
  bool operator==(const ListIterator<T> &it) const {
    return _currentNode == it._currentNode;
  }

  Node<T> *getNode() const { return _currentNode; }
  Node<T> *operator->() { return _currentNode; }
  ListIterator<T> &shift(int n) {
    while (n > 0) {
      ++(*this);
      n--;
    }
    return *this;
  }

 private:
  Node<T> *_currentNode;
};
}  // namespace s21
#endif  //  SRC_LIST_ITERATOR_H__
