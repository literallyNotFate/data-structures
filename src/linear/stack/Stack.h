#ifndef STACK_H
#define STACK_H

#include <Iterator.h>

#include <iostream>
#include <stdexcept>

// Stack

template <class T> class Stack {
private:
  T *stack;
  int top;
  int capacity;

public:
  // constructors
  inline explicit Stack<T>(const int capacity = 10)
      : capacity(capacity), top(-1) {
    this->stack = new T[capacity];
  };
  Stack<T>(const int &size, const T &value);
  Stack<T>(const int &size, T *arr);
  Stack<T>(const std::vector<T> &vec);
  template <typename Iterator> Stack<T>(Iterator begin, Iterator end);
  Stack<T>(const Stack<T> &other);

  Stack<T> &operator=(const Stack<T> &other);

  inline ~Stack<T>() {
    delete[] this->stack;
    this->stack = nullptr;
  };

  // resize array method
  void resize(const int &new_capacity);

  // getters
  inline T *get_stack() const { return this->stack; }
  inline int get_top() const { return this->top; }
  inline int get_capacity() const { return this->capacity; }
  inline int get_size() const { return (this->top + 1); }

  // bool methods
  inline bool is_empty() const { return this->top < 0; }
  inline bool is_full() const { return this->top >= (this->capacity - 1); }

  // adding to stack
  void push(const T &value);
  void insert(const int &index, const T &value);

  // deleting from stack
  T pop();

  // get element methods
  T peek() const;
  T bottom() const;
  T at(const int &index) const;
  inline T operator[](const int &index) const { return this->at(index); }

  inline Iterator<T> begin() const {
    return Iterator<T>(this->stack, this->get_size(), 0);
  }
  inline Iterator<T> end() const {
    return Iterator<T>(this->stack, this->get_size(), this->top);
  }

  // compare methods
  bool operator>(const Stack<T> &other) const;
  bool operator<(const Stack<T> &other) const;
  bool operator==(const Stack<T> &other) const;
  bool operator!=(const Stack<T> &other) const;
};

//----------
// Constructors
// ----------

// Fill constructor
template <typename T>
Stack<T>::Stack(const int &size, const T &value)
    : top(size - 1), capacity(size) {
  this->stack = new T[capacity];
  std::fill(this->stack, this->stack + size, value);
}

// Based on T* array constructor
template <typename T>
Stack<T>::Stack(const int &size, T *arr) : top(-1), capacity(size) {
  this->stack = new T[capacity];
  for (int i = 0; i < size; i++)
    this->push(arr[i]);
}

// Based on vector constructor
template <typename T>
Stack<T>::Stack(const std::vector<T> &vec) : top(-1), capacity(vec.size()) {
  this->stack = new T[vec.size()];
  for (int i = 0; i < vec.size(); i++)
    this->push(vec[i]);
}

// Based on range vector iterator constructor
template <typename T>
template <typename Iterator>
Stack<T>::Stack(Iterator begin, Iterator end) : top(-1) {
  if (begin >= end)
    throw std::invalid_argument(
        "The first iterator must be less than the second iterator!");

  this->capacity = std::distance(begin, end);
  this->stack = new T[this->capacity];

  for (Iterator it = begin; it != end; ++it)
    this->push(*it);
}

// Copy constructor (deep copy)
template <typename T>
Stack<T>::Stack(const Stack<T> &other)
    : top(other.top), capacity(other.capacity) {
  this->stack = new T[other.capacity];
  for (int i = 0; i < (this->top + 1); i++)
    this->stack[i] = other[i];
}

template <typename T> Stack<T> &Stack<T>::operator=(const Stack<T> &other) {
  if (this == &other)
    return *this;

  delete[] this->stack;

  this->top = other.top;
  this->capacity = other.capacity;
  this->stack = new T[other.capacity];

  for (int i = 0; i <= other.top; i++)
    this->stack[i] = other.stack[i];

  return *this;
}

// ----------
// Compare methods
// ----------

// Greater than
template <typename T> bool Stack<T>::operator>(const Stack<T> &other) const {
  if (this->get_size() > other.get_size())
    return true;

  if (this->get_size() < other.get_size())
    return false;

  int count = 0;
  for (int i = 0; i < this->get_size(); i++) {
    if (this->stack[i] > other[i])
      count++;
  }

  return count == this->get_size();
}

// Less than
template <typename T> bool Stack<T>::operator<(const Stack<T> &other) const {
  if (this->get_size() < other.get_size())
    return true;

  if (this->get_size() > other.get_size())
    return false;

  int count = 0;
  for (int i = 0; i < this->get_size(); i++) {
    if (this->stack[i] < other[i])
      count++;
  }

  return count == this->get_size();
}

// Equal to
template <typename T> bool Stack<T>::operator==(const Stack<T> &other) const {
  if (this->get_size() != other.get_size())
    return false;

  for (int i = 0; i < this->get_size(); i++) {
    if (this->stack[i] != other[i])
      return false;
  }

  return true;
}

// Not equal to
template <typename T> bool Stack<T>::operator!=(const Stack<T> &other) const {
  return !(*this == other);
}

// ---------
// Methods
// ---------

// Resize stack
template <typename T> void Stack<T>::resize(const int &new_capacity) {
  if (new_capacity <= this->capacity)
    return;

  T *new_stack = new T[new_capacity];
  if (this->stack != nullptr) {
    std::memcpy(new_stack, this->stack, (this->top + 1) * sizeof(T));
    delete[] this->stack;
  }

  this->stack = new_stack;
  this->capacity = new_capacity;
}

// Push to the stack
template <typename T> void Stack<T>::push(const T &value) {
  if (this->is_full())
    throw std::overflow_error("Stack overflow!");

  this->stack[++this->top] = value;
}

// Insert at given index
template <typename T> void Stack<T>::insert(const int &index, const T &value) {
  if (this->is_full())
    throw std::overflow_error("Stack overflow!");

  if (index < 0 || index > (this->top + 1))
    throw std::out_of_range("Provided index is out of range!");

  for (int i = top + 1; i >= index; --i) {
    this->stack[i] = this->stack[i - 1];
  }

  this->stack[index] = value;
  ++this->top;
}

// Pop from the stack
template <typename T> T Stack<T>::pop() {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  T popped = this->stack[this->top--];
  return popped;
}

// Get top element from the stack
template <typename T> T Stack<T>::peek() const {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  return this->stack[this->top];
}

template <typename T> T Stack<T>::bottom() const {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  return this->stack[0];
}

// Get by index
template <typename T> T Stack<T>::at(const int &index) const {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  if (index < 0 || index > this->get_size())
    throw std::out_of_range("Provided index is out of range!");

  return this->stack[index];
}

#endif
