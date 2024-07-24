#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include <stdexcept>

// Iterator

template <class T> class Iterator {
private:
  T *iter;
  int index;
  bool found;

public:
  // constructors
  inline Iterator<T>(T *iter, const int index = 0, const bool found = false)
      : iter(iter), index(index), found(found) {
    if (index < 0 || index > this->get_size())
      throw std::out_of_range("Index is out of range!");
  };

  inline Iterator<T>(const Iterator<T> &it, const bool found = false)
      : iter(it.iter), index(it.index), found(found) {
    if (index < 0 || index > this->get_size())
      throw std::out_of_range("Index is out of range!");
  };

  // getters
  inline T *get_iterable() const { return this->iter; }
  inline int get_index() const { return this->index; }

  // if provided index is in range
  inline static bool is_valid(const Iterator<T> &it, const int size) {
    return it.index >= 0 && it.index < size;
  }

  // calculate size
  inline int get_size() const {
    int count = 0;
    while (iter[count] != T()) {
      count++;
    }

    return count;
  }

  // increment operator
  inline Iterator<T> &operator++() {
    this->index++;
    return *this;
  }

  // get operator
  inline T &operator*() const {
    if (this->index < 0 || this->index > this->get_size())
      throw std::out_of_range("Index is out of range!");

    return this->iter[this->index];
  }

  // adding/substraction operations
  inline Iterator<T> operator+(const int &value) const {
    int new_index = this->index + value;
    if (new_index < 0 || new_index > this->get_size())
      throw std::out_of_range("Resulting index cannot be out of range!");

    return Iterator<T>(this->iter, new_index);
  }

  inline Iterator<T> operator-(const int &value) const {
    int new_index = this->index - value;
    if (new_index < 0 || new_index > this->get_size())
      throw std::out_of_range("Resulting index cannot be out of range!");

    return Iterator<T>(this->iter, new_index);
  }

  // comparing methods
  inline bool operator==(const Iterator<T> &other) const {
    return this->iter == other.iter && this->index == other.index &&
           this->found == other.found;
  }

  inline bool operator!=(const Iterator<T> &other) const {
    return !(*this == other);
  }

  inline bool operator<(const Iterator<T> &other) const {
    return this->index < other.index;
  }

  inline bool operator>(const Iterator<T> &other) const {
    return this->index > other.index;
  }
};

#endif
