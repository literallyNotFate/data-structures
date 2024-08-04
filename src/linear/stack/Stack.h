#ifndef STACK_H
#define STACK_H

#include <Iterator.h>

#include <iostream>
#include <sstream>
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

  // destructor
  inline ~Stack<T>() {
    delete[] this->stack;
    this->stack = nullptr;
  };

  // equal operator
  Stack<T> &operator=(const Stack<T> &other);

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
  bool contains(const T &value) const;

  // adding to stack
  void push(const T &value);
  void insert(const int &index, const T &value);

  // deleting from stack
  T pop();
  void erase(const Iterator<T> it);
  void erase_range(const Iterator<T> it1, const Iterator<T> it2);

  // get element methods
  T peek() const;
  T bottom() const;
  T at(const int &index) const;
  inline T operator[](const int &index) const { return this->at(index); }

  // find
  Iterator<T> find(const T &element) const;
  std::vector<Iterator<T>> find_all(const T &element) const;
  std::vector<Iterator<T>> find_if(std::function<bool(T)> fn) const;

  // replace
  void replace(const T &element, const T &replace);
  void replace(const Iterator<T> it, const T &replace);
  void replace_all(const T &element, const T &replace);
  void replace_if(std::function<bool(T)> fn, const T &replace);

  // converting methods
  inline const std::vector<T> to_vector() const {
    return std::vector<T>(this->stack, this->stack + this->get_size());
  }
  static inline Stack<T> from_vector(const std::vector<T> &vec) {
    return Stack<T>(vec);
  }
  const std::string to_string() const;

  // useful methods
  std::vector<T> top_n(const int &n) const;
  std::vector<T> bottom_n(const int &n) const;
  int count(const T &element) const;
  int count_if(std::function<bool(T)> fn) const;

  // min/max find
  T max() const;
  T max(std::function<int(T)> fn) const;
  T min() const;
  T min(std::function<int(T)> fn) const;

  // iterators
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
  for (T element : vec)
    this->push(element);
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

// Equal operator
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

// Erase element by given position of iterator
template <typename T> void Stack<T>::erase(const Iterator<T> it) {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  for (Iterator<T> it2 = it + 1; it2 != end() + 1; ++it2)
    *(it2 - 1) = *it2;

  --this->top;
}

// Erase element in give iterator range
template <typename T>
void Stack<T>::erase_range(const Iterator<T> it1, const Iterator<T> it2) {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  if (it1 > it2)
    throw std::invalid_argument("1st range must be less than 2nd!");

  for (Iterator<T> it = it2 + 1; it != end() + 1; ++it)
    *(it - (it2.get_index() - it1.get_index() + 1)) = *it;

  this->top -= (it2.get_index() - it1.get_index() + 1);
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

// Contains in stack
template <typename T> bool Stack<T>::contains(const T &value) const {
  Stack<T> st(*this);

  while (!st.is_empty()) {
    if (st.peek() == value)
      return true;

    st.pop();
  }

  return false;
}

// Find element in the stack
template <typename T> Iterator<T> Stack<T>::find(const T &element) const {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  for (Iterator<T> it = begin(); it != end() + 1; ++it) {
    if (*(it) == element)
      return Iterator<T>(it, true);
  }

  return end();
}

// Find all occurences of an element in the stack
template <typename T>
std::vector<Iterator<T>> Stack<T>::find_all(const T &element) const {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  std::vector<Iterator<T>> iterators;
  for (Iterator<T> it = begin(); it != end() + 1; ++it) {
    if (*it == element) {
      iterators.push_back(it);
    }
  }

  return iterators;
}

// Find all elements that satisfy the condition/predicate
template <typename T>
std::vector<Iterator<T>> Stack<T>::find_if(std::function<bool(T)> fn) const {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  std::vector<Iterator<T>> iterators;
  for (Iterator<T> it = begin(); it != end() + 1; ++it) {
    if (fn(*it))
      iterators.push_back(it);
  }

  return iterators;
}

// Replace first occurence of element
template <typename T>
void Stack<T>::replace(const T &element, const T &replace) {
  Iterator<T> el = this->find(element);
  if (el == end())
    throw std::invalid_argument("Element was not found!");

  *el = replace;
}

// Replace all occurrences of element
template <typename T>
void Stack<T>::replace_all(const T &element, const T &replace) {
  std::vector<Iterator<T>> items = this->find_all(element);
  if (items.size() == 0)
    throw std::invalid_argument("Element was not found!");

  for (Iterator<T> it : items)
    *it = replace;
}

// Replace all occurrences of element that satisfy the condition
template <typename T>
void Stack<T>::replace_if(std::function<bool(T)> fn, const T &replace) {
  std::vector<Iterator<T>> items = this->find_if(fn);
  for (Iterator<T> it : items)
    *it = replace;
}

// To string
template <typename T> const std::string Stack<T>::to_string() const {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  std::stringstream ss;
  Stack<T> st(*this);

  while (!st.is_empty()) {
    ss << st.peek() << std::endl;
    if ((st.get_size() - 1) != 0) {
      ss << "---" << std::endl;
    }

    st.pop();
  }

  return ss.str();
}

//----------
// Useful functions
// ----------

// Top n elements from the stack
template <typename T> std::vector<T> Stack<T>::top_n(const int &n) const {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  if (n < 0)
    throw std::invalid_argument("n should not be < 0!");

  if (n > (this->top + 1))
    throw std::invalid_argument("Provided n is out of range!");

  Stack<T> st(*this);
  std::vector<T> result;
  int count = 0;

  while (count < n) {
    result.push_back(st.peek());
    st.pop();
    count++;
  }

  return result;
}

// Bottom n elements from the stack
template <typename T> std::vector<T> Stack<T>::bottom_n(const int &n) const {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  if (n < 0)
    throw std::invalid_argument("n should not be < 0!");

  if (n > (this->top + 1))
    throw std::invalid_argument("Provided n is out of range!");

  std::vector<T> result;
  int count = 0, index = 0;

  while (count < n) {
    result.push_back(this->at(index));
    index++;
    count++;
  }

  return result;
}

// Count elements in the stack
template <typename T> int Stack<T>::count(const T &element) const {
  int count = 0;
  for (int i = 0; i < this->get_size(); i++) {
    if (this->stack[i] == element)
      count++;
  }

  return count;
}

// Count elements by the key/predicate
template <typename T> int Stack<T>::count_if(std::function<bool(T)> fn) const {
  int count = 0;
  for (int i = 0; i < this->get_size(); i++) {
    if (fn(this->stack[i]))
      count++;
  }

  return count;
}

//----------
// Min/max
// ----------

// Find max element
template <typename T> T Stack<T>::max() const {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  T max = this->stack[0];
  for (int i = 0; i < this->get_size(); i++) {
    if (max < this->stack[i])
      max = this->stack[i];
  }

  return max;
}

// Find max by key
template <typename T> T Stack<T>::max(std::function<int(T)> fn) const {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  T max = this->stack[0];
  for (int i = 0; i < this->get_size(); i++) {
    if (fn(max) < fn(this->stack[i]))
      max = this->stack[i];
  }

  return max;
}

// Find min element
template <typename T> T Stack<T>::min() const {
  if (this->is_empty())
    throw std::underflow_error("Stack underflow!");

  T min = this->stack[0];
  for (int i = 0; i < this->get_size(); i++) {
    if (min > this->stack[i])
      min = this->stack[i];
  }

  return min;
}

// Find min element by key
template <typename T> T Stack<T>::min(std::function<int(T)> fn) const {
  if (this->is_empty())
    throw std::underflow_error("Stack underlow!");

  T min = this->stack[0];
  for (int i = 0; i < this->get_size(); i++) {
    if (fn(min) > fn(this->stack[i]))
      min = this->stack[i];
  }

  return min;
}

#endif
