#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <stdexcept>

// Dynamic array

template <class T> class DynamicArray {
private:
  T *array;
  int size;
  int capacity;

public:
  // constructors
  inline explicit DynamicArray<T>() : array(nullptr), size(0), capacity(0){};
  inline explicit DynamicArray<T>(const int &capacity)
      : size(0), capacity(capacity) {
    this->array = new T[capacity];
  }
  DynamicArray<T>(const int &size, const T &value);
  DynamicArray<T>(const int &size, T *arr);
  DynamicArray<T>(const DynamicArray<T> &other);

  // specified constructors
  DynamicArray<int>(const int &size, const int &min, const int &max);
  DynamicArray<char>(const std::string &str);

  // equal operator
  DynamicArray<T> &operator=(const DynamicArray<T> &other);

  // destructor
  inline ~DynamicArray<T>() {
    delete[] array;
    this->array = nullptr;
  }

  // resize array method
  void resize(const int &capacity);

  // getters
  inline T *get_array() const { return this->array; }
  inline int get_size() const { return this->size; }
  inline int get_capacity() const { return this->capacity; }

  // bool methods
  inline bool is_empty() const { return this->size == 0; }
  inline bool is_full() const { return this->size >= this->capacity; }
  bool contains(const T &value) const;

  // get element
  T at(const int &index) const;
  inline T operator[](const int &index) const { return this->at(index); }

  // adding to the array methods
  void push_back(const T &value);
  void push_begin(const T &value);
  void insert(const int &index, const T &value);

  // compare methods
  bool operator>(const DynamicArray<T> &other) const;
  bool operator<(const DynamicArray<T> &other) const;
  bool operator==(const DynamicArray<T> &other) const;
  bool operator!=(const DynamicArray<T> &other) const;
};

//----------
// Constructors
// ----------

// Fill constructor
template <typename T>
DynamicArray<T>::DynamicArray(const int &size, const T &value)
    : size(size), capacity(size) {
  this->array = new T[capacity];
  std::fill(this->array, this->array + size, value);
}

// Based on T* array constructor
template <typename T>
DynamicArray<T>::DynamicArray(const int &size, T *arr)
    : size(size), capacity(size) {
  this->array = new T[capacity];
  std::copy(this->array, this->array + size, arr);
}

// Copy constructor (deep copy)
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray &other)
    : size(other.size), capacity(other.capacity) {
  this->array = new T[other.capacity];
  for (int i = 0; i < this->size; i++)
    this->array[i] = other[i];
}

// Fill int array with random numbers from range
template <>
inline DynamicArray<int>::DynamicArray(const int &size, const int &min,
                                       const int &max)
    : size(size), capacity(size) {
  this->array = new int[capacity];

  static bool seed_initialized = false;
  if (!seed_initialized) {
    std::srand(static_cast<unsigned>(std::time(0)));
    seed_initialized = true;
  }

  for (int i = 0; i < size; i++) {
    int num = min + std::rand() % ((max + 1) - min);
    this->array[i] = num;
  }
}

// Form array from string
template <>
inline DynamicArray<char>::DynamicArray(const std::string &str)
    : size(str.size()), capacity(str.size()) {

  this->array = new char[this->capacity];
  for (int i = 0; i < this->size; i++) {
    this->array[i] = str[i];
  }
}

// Equal operator
template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &other) {
  if (this != &other) {
    delete[] array;

    this->size = other.size;
    this->capacity = other.capacity;
    this->array = new T[other.capacity];

    for (int i = 0; i < this->size; i++)
      this->array[i] = other[i];
  }

  return *this;
}

// ---------
// Methods
// ---------

// Resize array
template <typename T> void DynamicArray<T>::resize(const int &capacity) {
  T *new_array = new T[capacity];
  if (this->array != nullptr) {
    std::memcpy(new_array, this->array, this->size * sizeof(T));
    delete[] this->array;
  }

  this->array = new_array;
  this->capacity = capacity;
}

// Contains element in array
template <typename T> bool DynamicArray<T>::contains(const T &value) const {
  for (int i = 0; i < this->size; i++) {
    if (this->array[i] == value)
      return true;
  }

  return false;
}

// Get element by index from array
template <typename T> T DynamicArray<T>::at(const int &index) const {
  if (index < 0 || index >= this->size)
    throw std::out_of_range("Provided index is out of range!");

  return this->array[index];
}

// Push back
template <typename T> void DynamicArray<T>::push_back(const T &value) {
  if (this->is_full())
    throw std::length_error("Array is full, try to resize it!");

  this->array[this->size++] = value;
}

// Push begin
template <typename T> void DynamicArray<T>::push_begin(const T &value) {
  if (this->is_full())
    throw std::length_error("Array is full, try to resize it!");

  for (int i = ++this->size; i > 0; i--)
    this->array[i] = this->array[i - 1];

  this->array[0] = value;
}

// Insert at given index
template <typename T>
void DynamicArray<T>::insert(const int &index, const T &value) {
  if (this->is_full())
    throw std::length_error("Array is full, try to resize it!");

  if (index < 0 || index >= this->size)
    throw std::out_of_range("Provided index is out of range!");

  for (int i = ++this->size; i >= index; i--)
    this->array[i] = this->array[i - 1];

  this->array[index] = value;
}

// ----------
// Compare methods
// ----------

// Greater than
template <typename T>
bool DynamicArray<T>::operator>(const DynamicArray<T> &other) const {
  if (this->size > other.size)
    return true;

  if (this->size < other.size)
    return false;

  int count = 0;
  for (int i = 0; i < this->size; i++) {
    if (this->array[i] > other[i])
      count++;
  }

  return count == this->size;
}

// Less than
template <typename T>
bool DynamicArray<T>::operator<(const DynamicArray<T> &other) const {
  if (this->size < other.size)
    return true;

  if (this->size > other.size)
    return false;

  int count = 0;
  for (int i = 0; i < this->size; i++) {
    if (this->array[i] < other[i])
      count++;
  }

  return count == this->size;
}

// Equal to
template <typename T>
bool DynamicArray<T>::operator==(const DynamicArray<T> &other) const {
  if (this->size != other.size)
    return false;

  for (int i = 0; i < this->size; i++) {
    if (this->array[i] != other[i])
      return false;
  }

  return true;
}

// Not equal to
template <typename T>
bool DynamicArray<T>::operator!=(const DynamicArray<T> &other) const {
  return !(*this == other);
}

#endif
