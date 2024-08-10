#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <Iterator.h>

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <unordered_set>
#include <utility>
#include <vector>

// Dynamic array

template <class T> class DynamicArray {
private:
  T *array;
  int size;
  int capacity;

  // merge sort helper functions
  void merge_sort_helper(int left, int right, std::function<bool(T, T)> comp);
  void merge(int left, int mid, int right, std::function<bool(T, T)> comp);

public:
  // constructors
  inline explicit DynamicArray<T>() : array(nullptr), size(0), capacity(0){};
  inline explicit DynamicArray<T>(const int &capacity)
      : size(0), capacity(capacity) {
    this->array = new T[capacity];
  }
  DynamicArray<T>(const int &size, const T &value);
  DynamicArray<T>(const int &size, T *arr);
  DynamicArray<T>(const std::vector<T> &vec);
  template <typename Iterator> DynamicArray<T>(Iterator begin, Iterator end);
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
  void insert(const int &index, const std::vector<T> &vec);

  // removing from array
  void erase_back();
  void erase_begin();
  void erase(const Iterator<T> it);
  void erase_range(const Iterator<T> it1, const Iterator<T> it2);
  void erase_all(const T &element);
  void erase_if(std::function<bool(T)> fn);

  // find
  Iterator<T> find(const T &element) const;
  std::vector<Iterator<T>> find_all(const T &element) const;
  std::vector<Iterator<T>> find_if(std::function<bool(T)> fn) const;

  // replace
  void replace(const T &element, const T &replace);
  void replace(const Iterator<T> it, const T &replace);
  void replace_all(const T &element, const T &replace);
  void replace_if(std::function<bool(T)> fn, const T &replace);
  void replace_range(const Iterator<T> it1, const Iterator<T> it2,
                     const T &replace);

  // converting methods
  inline const std::vector<T> to_vector() const {
    return std::vector<T>(this->array, this->array + this->get_size());
  }
  static inline DynamicArray<T> from_vector(const std::vector<T> &vec) {
    return DynamicArray<T>(vec);
  }
  const std::string to_string() const;

  // useful functions
  int count(const T &element) const;
  int count_if(std::function<bool(T)> fn) const;
  DynamicArray<T> filter(std::function<bool(T)> fn) const;
  void map(std::function<void(T)> fn) const;
  DynamicArray<T> apply(std::function<T(T)> fn) const;
  T reduce(T init, std::function<T(T, T)> fn = std::plus<T>()) const;
  void reverse();
  DynamicArray<T> reversed() const;
  void reverse_partial(const Iterator<T> it1, const Iterator<T> it2);
  DynamicArray<T> reversed_partial(const Iterator<T> it1,
                                   const Iterator<T> it2) const;
  DynamicArray<T> remove_duplicates() const;
  std::map<T, int> frequency_map() const;
  static void swap(DynamicArray<T> &a, DynamicArray<T> &b);

  // min/max find
  T max() const;
  T max(std::function<int(T)> fn) const;
  T min() const;
  T min(std::function<int(T)> fn) const;

  // sorting
  void bubble_sort(std::function<bool(T, T)> comp = std::less<T>());
  void selection_sort(std::function<bool(T, T)> comp = std::less<T>());
  void merge_sort(std::function<bool(T, T)> comp = std::less<T>());

  // union
  DynamicArray<T> operator|(const DynamicArray<T> &other) const;
  // intersect
  DynamicArray<T> operator&(const DynamicArray<T> &other) const;
  // merge
  DynamicArray<T> operator+(const DynamicArray<T> &other) const;

  // iterators
  inline Iterator<T> begin() const {
    return Iterator<T>(this->array, this->size);
  }
  inline Iterator<T> end() const {
    return Iterator<T>(this->array, this->size, this->size - 1);
  }

  // compare methods
  bool operator>(const DynamicArray<T> &other) const;
  bool operator<(const DynamicArray<T> &other) const;
  bool operator==(const DynamicArray<T> &other) const;
  bool operator!=(const DynamicArray<T> &other) const;

  // some functions
  Iterator<T> distinct() const;
  std::vector<Iterator<T>> distinct_all() const;
  Iterator<T> kth_distinct(const int &k) const;
  std::vector<T> top_k_frequent(const int &k) const;
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
  for (int i = 0; i < this->size; i++)
    this->array[i] = arr[i];
}

// Based on vector constructor
template <typename T>
DynamicArray<T>::DynamicArray(const std::vector<T> &vec)
    : size(vec.size()), capacity(vec.size()) {
  this->array = new T[vec.size()];
  for (int i = 0; i < this->size; i++)
    this->array[i] = vec[i];
}

// Based on range vector iterator constructor
template <typename T>
template <typename Iterator>
DynamicArray<T>::DynamicArray(Iterator begin, Iterator end) {
  if (begin >= end)
    throw std::invalid_argument(
        "The first iterator must be less than the second iterator!");

  this->size = this->capacity = std::distance(begin, end);
  this->array = new T[this->size];

  int i = 0;
  for (Iterator it = begin; it != end; ++it, ++i)
    this->array[i] = *it;
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

// ---------
// Methods
// ---------

// Resize array
template <typename T> void DynamicArray<T>::resize(const int &new_capacity) {
  if (new_capacity <= this->capacity)
    return;

  T *new_array = new T[new_capacity];
  if (this->array != nullptr) {
    std::memcpy(new_array, this->array, this->size * sizeof(T));
    delete[] this->array;
  }

  this->array = new_array;
  this->capacity = new_capacity;
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
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

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

// Insert vector at given index
template <typename T>
void DynamicArray<T>::insert(const int &index, const std::vector<T> &vec) {
  if (this->is_full())
    throw std::length_error("Array is full, try to resize it!");

  if (index < 0 || index >= this->size)
    throw std::out_of_range("Provided index is out of range!");

  if (this->size + vec.size() > this->capacity)
    this->resize(this->size + vec.size());

  for (int i = this->size - 1; i >= index; --i)
    this->array[i + vec.size()] = this->array[i];

  for (int i = 0; i < vec.size(); ++i)
    this->array[index + i] = vec[i];

  this->size += vec.size();
}

// Erase from back
template <typename T> void DynamicArray<T>::erase_back() {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  this->size--;
}

// Erase from begin
template <typename T> void DynamicArray<T>::erase_begin() {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  for (int i = 0; i < this->size - 1; i++) {
    this->array[i] = this->array[i + 1];
  }

  this->size--;
}

// Erase element by given position of iterator
template <typename T> void DynamicArray<T>::erase(const Iterator<T> it) {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  for (Iterator<T> it2 = it + 1; it2 != end() + 1; ++it2)
    *(it2 - 1) = *it2;

  --this->size;
}

// Erase element in give iterator range
template <typename T>
void DynamicArray<T>::erase_range(const Iterator<T> it1,
                                  const Iterator<T> it2) {
  if (it1 > it2)
    throw std::invalid_argument("1st range must be less than 2nd!");

  for (Iterator<T> it = it2 + 1; it != end() + 1; ++it)
    *(it - (it2.get_index() - it1.get_index() + 1)) = *it;

  this->size -= (it2.get_index() - it1.get_index() + 1);
}

// Erase all occurrences of an element
template <typename T> void DynamicArray<T>::erase_all(const T &element) {
  std::vector<Iterator<T>> items = this->find_all(element);
  for (auto it = items.rbegin(); it != items.rend(); ++it)
    this->erase(*it);
}

// Erase element by predicate
template <typename T>
void DynamicArray<T>::erase_if(std::function<bool(T)> fn) {
  std::vector<Iterator<T>> items = this->find_if(fn);
  for (auto it = items.rbegin(); it != items.rend(); ++it)
    this->erase(*it);
}

// Find element in the stack
template <typename T>
Iterator<T> DynamicArray<T>::find(const T &element) const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  for (Iterator<T> it = begin(); it != end(); ++it) {
    if (*it == element)
      return Iterator<T>(it, true);
  }

  return end();
}

// Find all elements in the stack
template <typename T>
std::vector<Iterator<T>> DynamicArray<T>::find_all(const T &element) const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  std::vector<Iterator<T>> iterators;
  for (Iterator<T> it = begin(); it != end() + 1; ++it) {
    if (*it == element)
      iterators.push_back(it);
  }

  return iterators;
}

// Find all elements that satisfy the condition/predicate
template <typename T>
std::vector<Iterator<T>>
DynamicArray<T>::find_if(std::function<bool(T)> fn) const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  std::vector<Iterator<T>> iterators;
  for (Iterator<T> it = begin(); it != end() + 1; ++it) {
    if (fn(*it))
      iterators.push_back(it);
  }

  return iterators;
}

// Replace given element
template <typename T>
void DynamicArray<T>::replace(const T &element, const T &replace) {
  Iterator<T> el = this->find(element);
  if (el == end())
    throw std::invalid_argument("Element was not found!");

  *el = replace;
}

// Replace at given iterator
template <typename T>
void DynamicArray<T>::replace(const Iterator<T> it, const T &replace) {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  *it = replace;
}

// Replace all occurrences of element
template <typename T>
void DynamicArray<T>::replace_all(const T &element, const T &replace) {
  std::vector<Iterator<T>> items = this->find_all(element);
  if (items.size() == 0)
    throw std::invalid_argument("Elements were not found!");

  for (Iterator<T> it : items)
    *it = replace;
}

// Replace all occurrences of element that satisfy the condition
template <typename T>
void DynamicArray<T>::replace_if(std::function<bool(T)> fn, const T &replace) {
  std::vector<Iterator<T>> items = this->find_if(fn);
  for (Iterator<T> it : items)
    *it = replace;
}

// Replace all elements in a range
template <typename T>
void DynamicArray<T>::replace_range(const Iterator<T> it1,
                                    const Iterator<T> it2, const T &replace) {
  if (it1 > it2)
    throw std::invalid_argument("1st range must be less than 2nd!");

  for (Iterator<T> it = it1; it != it2; ++it)
    *it = replace;

  *it2 = replace;
}

// Swapping two dynamic arrays
template <typename T>
void DynamicArray<T>::swap(DynamicArray<T> &a, DynamicArray<T> &b) {
  DynamicArray<T> temp = a;
  a = b;
  b = temp;
}

//----------
// Useful functions
// ----------

// To string
template <typename T> const std::string DynamicArray<T>::to_string() const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  std::stringstream ss;
  for (Iterator<T> it = begin(); it != end() + 1; ++it) {
    if (it != begin())
      ss << ", ";

    ss << *it;
  }

  ss << ".";
  return ss.str();
}

// Count element
template <typename T> int DynamicArray<T>::count(const T &element) const {
  int count = 0;
  for (int i = 0; i < this->size; i++) {
    if (this->array[i] == element)
      count++;
  }

  return count;
}

// Count element by predicate
template <typename T>
int DynamicArray<T>::count_if(std::function<bool(T)> fn) const {
  int count = 0;
  for (int i = 0; i < this->size; i++) {
    if (fn(this->array[i]))
      count++;
  }

  return count;
}

// Filter elemets in the array
template <typename T>
DynamicArray<T> DynamicArray<T>::filter(std::function<bool(T)> fn) const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  DynamicArray<T> result(this->capacity);
  for (int i = 0; i < this->size; i++) {
    if (fn(this->array[i]))
      result.push_back(this->array[i]);
  }

  if (result.get_size() == 0)
    return *this;

  return result;
}

// Map array elements
template <typename T>
void DynamicArray<T>::map(std::function<void(T)> fn) const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  for (int i = 0; i < this->size; i++)
    fn(this->array[i]);
}

// Apply function to array
template <typename T>
DynamicArray<T> DynamicArray<T>::apply(std::function<T(T)> fn) const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  DynamicArray<T> result(this->capacity);
  for (int i = 0; i < this->size; i++) {
    T value = fn(this->array[i]);
    result.push_back(value);
  }

  return result;
}

// Reduce
template <typename T>
T DynamicArray<T>::reduce(T init, std::function<T(T, T)> fn) const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  for (int i = 0; i < this->size; i++)
    init = fn(init, this->array[i]);

  return init;
}

// Reverse array (modify the existing)
template <typename T> void DynamicArray<T>::reverse() {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  int i = 0, j = this->size - 1;
  while (i < j) {
    std::swap(this->array[i], this->array[j]);
    i++;
    j--;
  }
}

// Reverse array (creating new array)
template <typename T> DynamicArray<T> DynamicArray<T>::reversed() const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  DynamicArray<T> result(this->capacity);
  for (int i = 0; i < this->size; i++)
    result.push_begin(this->array[i]);

  return result;
}

// Reverse partial (modify the existing)
template <typename T>
void DynamicArray<T>::reverse_partial(const Iterator<T> it1,
                                      const Iterator<T> it2) {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  if (it1 >= it2)
    throw std::invalid_argument("1st iterator must be less than 2nd iterator!");

  Iterator<T> begin = it1, end = it2;
  while (begin < end) {
    std::swap(*begin, *end);
    ++begin;
    --end;
  }
}

// Remove duplicates from array
template <typename T>
DynamicArray<T> DynamicArray<T>::remove_duplicates() const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  DynamicArray<T> result(this->capacity);
  std::unordered_set<T> seen;
  for (int i = 0; i < this->size; i++) {
    if (seen.find(this->array[i]) == seen.end()) {
      seen.insert(this->array[i]);
      result.push_back(this->array[i]);
    }
  }

  return result;
}

// Get frequency map of dynamic array
template <typename T> std::map<T, int> DynamicArray<T>::frequency_map() const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  std::map<T, int> fm;
  for (int i = 0; i < this->size; i++)
    fm[this->array[i]]++;

  return fm;
}

//----------
// Min/max
// ----------

// Find max element
template <typename T> T DynamicArray<T>::max() const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  T max = this->array[0];
  for (int i = 0; i < this->size; i++) {
    if (max < this->array[i])
      max = this->array[i];
  }

  return max;
}

// Find max by key
template <typename T> T DynamicArray<T>::max(std::function<int(T)> fn) const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  T max = this->array[0];
  for (int i = 0; i < this->size; i++) {
    if (fn(max) < fn(this->array[i]))
      max = this->array[i];
  }

  return max;
}

// Find min element
template <typename T> T DynamicArray<T>::min() const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  T min = this->array[0];
  for (int i = 0; i < this->size; i++) {
    if (min > this->array[i])
      min = this->array[i];
  }

  return min;
}

// Find min element by key
template <typename T> T DynamicArray<T>::min(std::function<int(T)> fn) const {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  T min = this->array[0];
  for (int i = 0; i < this->size; i++) {
    if (fn(min) > fn(this->array[i]))
      min = this->array[i];
  }

  return min;
}

//----------
// Sorting
// ----------

// Bubble sort
template <typename T>
void DynamicArray<T>::bubble_sort(std::function<bool(T, T)> comp) {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  for (int i = 0; i < this->size - 1; i++) {
    for (int j = 0; j < this->size - i - 1; j++) {
      if (comp(this->array[j + 1], this->array[j]))
        std::swap(this->array[j], this->array[j + 1]);
    }
  }
}

// Selection sort
template <typename T>
void DynamicArray<T>::selection_sort(std::function<bool(T, T)> comp) {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  for (int i = 0; i < this->size - 1; i++) {
    int min_index = i;
    for (int j = i + 1; j < this->size; j++) {
      if (comp(this->array[j], this->array[min_index]))
        min_index = j;
    }

    std::swap(this->array[i], this->array[min_index]);
  }
}

// Merge sort
template <typename T>
void DynamicArray<T>::merge_sort(std::function<bool(T, T)> comp) {
  if (this->is_empty())
    throw std::length_error("Array is empty, try to add elements!");

  merge_sort_helper(0, this->size - 1, comp);
}

// Merge sort helper function
template <typename T>
void DynamicArray<T>::merge_sort_helper(int left, int right,
                                        std::function<bool(T, T)> comp) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    merge_sort_helper(left, mid, comp);
    merge_sort_helper(mid + 1, right, comp);
    merge(left, mid, right, comp);
  }
}

template <typename T>
void DynamicArray<T>::merge(int left, int mid, int right,
                            std::function<bool(T, T)> comp) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  T *L = new T[n1];
  T *R = new T[n2];

  for (int i = 0; i < n1; i++)
    L[i] = this->array[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = this->array[mid + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (comp(L[i], R[j])) {
      this->array[k] = L[i];
      i++;
    } else {
      this->array[k] = R[j];
      j++;
    }

    k++;
  }

  while (i < n1) {
    this->array[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    this->array[k] = R[j];
    j++;
    k++;
  }

  delete[] L;
  delete[] R;
}

//----------
// Set operations
// ----------

// Union of two arrays
template <typename T>
DynamicArray<T> DynamicArray<T>::operator|(const DynamicArray<T> &other) const {
  if (this->is_empty() || other.is_empty())
    throw std::length_error("One of arrays is empty!");

  DynamicArray<T> result(this->capacity + other.get_capacity());
  std::unordered_set<T> seen;

  for (int i = 0; i < this->size; i++) {
    if (seen.find(this->array[i]) == seen.end()) {
      seen.insert(this->array[i]);
      result.push_back(this->array[i]);
    }
  }

  for (int i = 0; i < other.get_size(); i++) {
    if (seen.find(other[i]) == seen.end()) {
      seen.insert(other[i]);
      result.push_back(other[i]);
    }
  }

  return result;
}

// Intersection of two arrays
template <typename T>
DynamicArray<T> DynamicArray<T>::operator&(const DynamicArray<T> &other) const {
  if (this->is_empty() || other.is_empty())
    throw std::length_error("One of arrays is empty!");

  DynamicArray<T> result(this->size);
  std::unordered_set<T> seen;
  std::unordered_set<T> result_set;

  for (int i = 0; i < this->size; i++)
    seen.insert(this->array[i]);

  for (int i = 0; i < other.get_size(); i++) {
    if (seen.find(other[i]) != seen.end() &&
        result_set.find(other[i]) == result_set.end()) {
      result.push_back(other[i]);
      result_set.insert(other[i]);
    }
  }

  return result;
}

// Merge two arrays
template <typename T>
DynamicArray<T> DynamicArray<T>::operator+(const DynamicArray<T> &other) const {
  if (this->is_empty() || other.is_empty())
    throw std::length_error("One of arrays is empty!");

  DynamicArray<T> result(*this);
  result.resize(result.get_size() + other.get_size());

  for (int i = 0; i < other.get_size(); i++)
    result.push_back(other[i]);

  return result;
}

//----------
// Some functions
// ----------

// Getting the first element that appears once in the array
template <typename T> Iterator<T> DynamicArray<T>::distinct() const {
  std::map<T, int> fm = this->frequency_map();
  for (Iterator<T> it = this->begin(); it != this->end(); ++it) {
    if (fm[*it] == 1)
      return Iterator<T>(it, true);
  }

  return end();
}

// All distinct elements
template <typename T>
std::vector<Iterator<T>> DynamicArray<T>::distinct_all() const {
  std::vector<Iterator<T>> distincts;
  std::map<T, int> fm = this->frequency_map();
  for (Iterator it = this->begin(); it != this->end(); ++it) {
    if (fm[*it] == 1)
      distincts.push_back(it);
  }

  return distincts;
}

// Kth distinct element in the array
template <typename T>
Iterator<T> DynamicArray<T>::kth_distinct(const int &k) const {
  int kth = k;
  std::map<T, int> fm = this->frequency_map();
  for (Iterator<T> it = this->begin(); it != this->end(); ++it) {
    if (fm[*it] == 1)
      --kth;

    if (kth == 0)
      return Iterator<T>(it, true);
  }

  return end();
}

// Top k frequent elements from the array
template <typename T>
std::vector<T> DynamicArray<T>::top_k_frequent(const int &k) const {
  std::map<T, int> fm = this->frequency_map();

  auto comp = [](std::pair<T, int> &a, std::pair<T, int> &b) {
    return a.second < b.second;
  };

  std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>,
                      decltype(comp)>
      heap(comp);

  for (std::pair<T, int> entry : fm)
    heap.push({entry.first, entry.second});

  std::vector<T> result;
  int count = k;
  while (count > 0) {
    result.push_back(heap.top().first);
    heap.pop();
    --count;
  }

  return result;
}

#endif
