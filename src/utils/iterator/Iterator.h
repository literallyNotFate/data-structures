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

  // get operator
  inline T &operator*() const {
    if (this->index < 0 || this->index > this->size)
      throw std::out_of_range("Index is out of range!");

    return this->iter[this->index];
  }

  // adding/substraction operations
  inline Iterator<T> operator+(const int &value) const {
    int new_index = this->index + value;
    if (new_index < 0 || new_index > this->size)
      throw std::out_of_range("Resulting index cannot be out of range!");

    return Iterator<T>(this->iter, this->size, new_index);
  }

  inline Iterator<T> operator-(const int &value) const {
    int new_index = this->index - value;
    if (new_index < 0 || new_index > this->size)
      throw std::out_of_range("Resulting index cannot be out of range!");

    return Iterator<T>(this->iter, this->size, new_index);
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