#ifndef SRC_NODE_H__
#define SRC_NODE_H__

namespace s21 {
template <typename T>
class Node {
 public:
  Node *pnext;
  Node *prev;
  T data;
  Node(T data = T(), Node *pnext = nullptr, Node *prev = nullptr) {
    this->pnext = pnext;
    this->prev = prev;
    this->data = data;
  }
};
}  // namespace s21

#endif  // SRC_NODE_H__