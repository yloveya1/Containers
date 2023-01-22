#ifndef SRC_S21_ARRAY_H
#define SRC_S21_ARRAY_H

#include <initializer_list>
#include <utility>

namespace s21 {
template <typename T, std::size_t N = 0>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  array() { fill(T()); }

  array(std::initializer_list<value_type> const &items) {
    size_type i = 0;
    for (auto obj : items) {
      array_[i] = obj;
      i++;
      if (i == N) {
        break;
      }
    }
    if (i < N) {
      while (i != N) {
        array_[i] = T();
        i++;
      }
    }
  }

  array(const array &a) {
    for (size_type i = 0; i < N; i++) {
      array_[i] = a.array_[i];
    }
  }

  array(array &&a) { *this = std::move(a); }
  ~array() {}

  array &operator=(array &&a) {
    std::move(std::begin(a.array_), std::end(a.array_), &array_[0]);
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("pos >= N");
    }
    return array_[pos];
  }

  reference operator[](size_type pos) { return array_[pos]; }
  const_reference front() const { return *array_; }
  const_reference back() const { return *(array_ + N - 1); }
  iterator data() { return array_; }

  iterator begin() { return array_; }
  iterator end() { return array_ + N; }

  bool empty() const { return N == 0; }
  size_type size() const { return N; }
  size_type max_size() const { return N; }

  void swap(array &other) {
    array<T, N> buffer(other);
    for (size_type i = 0; i < N; i++) {
      other.array_[i] = array_[i];
      array_[i] = buffer.array_[i];
    }
  }

  void fill(const_reference value) {
    for (int i = 0; i < (int)N; i++) {
      array_[i] = value;
    }
  }

 private:
  value_type array_[N];
};
}  // namespace s21

#endif  //  SRC_S21_ARRAY_H