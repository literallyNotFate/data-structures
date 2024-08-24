#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include <stdexcept>

// Iterator

template <class T> class Iterator {
private:
  T *iter;
  int index;
  int size;
  bool found;

public:
  // constructors
  inline Iterator<T>(T *iter, const int size, const int index = 0,
                     const bool found = false)
      : iter(iter), size(size), index(index), found(found) {
    if (index < 0 || index > size)
      throw std::out_of_range("Index is out of range!");
  };

  inline Iterator<T>(const Iterator<T> &it, const bool found = false)
      : iter(it.iter), size(it.size), index(it.index), found(found) {
    if (index < 0 || index > size)
      throw std::out_of_range("Index is out of range!");
  };

  // getters
  inline T *get_iterable() const { return this->iter; }
  inline int get_size() const { return this->size; }
  inline int get_index() const { return this->index; }

  // increment operator
  inline Iterator<T> &operator++() {
    ++this->index;
    return *this;
  }

  // decrement operator
  inline Iterator<T> &operator--() {
    --this->index;
    return *this;
  }

  // get operatorы
  inline T &operator*() const {
    if (this->index < 0 || this->index > this->size)
      throw std::out_of_range("Index is out of range!");

    return this->iter[this->index];
  }

  inline T *operator->() const {
    if (this->index < 0 || this->index >= this->size)
      throw std::out_of_range("Index is out of range!");

    return &this->iter[this->index];
  }

  // adding operation
  inline Iterator<T> operator+(const int &value) const {
    int new_index = this->index + value;
    if (new_index < 0 || new_index > this->size)
      throw std::out_of_range("Resulting index cannot be out of range!");

    return Iterator<T>(this->iter, this->size, new_index);
  }

  // substraction operation
  inline Iterator<T> operator-(const int &value) const {
    int new_index = this->index - value;
    if (new_index < 0 || new_index > this->size)
      throw std::out_of_range("Resulting index cannot be out of range!");

    return Iterator<T>(this->iter, this->size, new_index);
  }

  // advance method
  inline static void advance(Iterator<T> &it, int pos) {
    int n = pos;
    if (pos > 0) {
      int remaining = it.size - it.index - 1;
      n = std::min(pos, remaining);
    } else {
      n = std::max(pos, -static_cast<int>(it.index));
    }

    it.index += n;
  };

  // equals to
  inline bool operator==(const Iterator<T> &other) const {
    return this->iter == other.iter && this->index == other.index &&
           this->found == other.found;
  }

  // not equals to
  inline bool operator!=(const Iterator<T> &other) const {
    return !(*this == other);
  }

  // less than
  inline bool operator<(const Iterator<T> &other) const {
    return this->index < other.index;
  }

  // greater than
  inline bool operator>(const Iterator<T> &other) const {
    return this->index > other.index;
  }

  // less equal than
  inline bool operator<=(const Iterator<T> &other) const {
    return this->index <= other.index;
  }

  // greater equal than
  inline bool operator>=(const Iterator<T> &other) const {
    return this->index >= other.index;
  }
};

#endif
