#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "../set/s21_set.h"

namespace s21 {

//  ________________________MULTISET_CLASS______________________________________

template <typename Key>
class multiset : public set<Key> {
 public:
  using key_type = Key;
  using value_type = const key_type;
  using set<Key>::set;

  multiset(std::initializer_list<value_type> const &items);
  bool insertCompare(const Key &value, NodeSet<Key> *parent) {
    return value <= parent->data;
  }

};  // multiset

//  _______________________MULTISET_METHODS_____________________________________
template <typename Key>
multiset<Key>::multiset(std::initializer_list<const Key> const &items)
    : multiset() {
  for (auto key : items) {
    this->insert(key);
  }
}

}  //  namespace s21

#endif