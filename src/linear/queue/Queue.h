#ifndef QUEUE_H
#define QUEUE_H

#include <QueueIterator.h>

#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

// Queue node class

template <class T> class QueueNode {
public:
  T data;
  QueueNode<T> *next;
  QueueNode(const T &data) : data(data), next(nullptr) {}
};

// Queue on linked list

template <class T> class Queue {
private:
  QueueNode<T> *head;
  QueueNode<T> *tail;
  int length;

public:
  // constructors
  inline explicit Queue<T>() : head(nullptr), tail(nullptr), length(0){};
  Queue<T>(std::vector<T> vec);
  template <typename Iterator> Queue<T>(Iterator begin, Iterator end);
  Queue<T>(const Queue<T> &other);

  // destructor
  inline ~Queue<T>() { this->clear(); }

  // equal oeprator
  Queue<T> &operator=(const Queue<T> &other);

  // getters
  inline T get_first() const { return this->head->data; }
  inline T get_last() const { return this->tail->data; }
  inline QueueNode<T> *get_head() const { return this->head; }
  inline QueueNode<T> *get_tail() const { return this->tail; }
  inline int get_length() const { return this->length; }
  int get_index(const QueueNode<T> *node) const;
  int get_index(const T &element) const;

  // bool methods
  inline bool is_empty() const { return this->head == nullptr; }
  bool contains(const T &element) const;

  // accessing element
  QueueNode<T> *at(const int &index) const;
  inline QueueNode<T> *operator[](const int &index) { return this->at(index); }

  // adding to the queue
  void enqueue(const T &element);
  void insert(const QueueIterator<T> qit, const T &element);
  void insert(const QueueIterator<T> qit, const std::vector<T> &vec);

  // erasing from the queue
  T dequeue();
  void erase(const T &element);
  void erase(const QueueIterator<T> qit);
  void erase_all(const T &element);

  // find
  QueueIterator<T> find(const T &element) const;
  std::vector<QueueIterator<T>> find_all(const T &element) const;
  std::vector<QueueIterator<T>> find_if(std::function<bool(T)> fn) const;

  // replace
  void replace(const T &element, const T &replace);
  void replace(const QueueIterator<T> qit, const T &replace);
  void replace_all(const T &element, const T &replace);
  void replace_if(std::function<bool(T)> fn, const T &replace);
  void replace_range(const QueueIterator<T> qit1, const QueueIterator<T> qit2,
                     const T &replace);

  // converting methods
  const std::vector<T> to_vector() const;
  static inline Queue<T> from_vector(const std::vector<T> &vec) {
    return Queue<T>(vec);
  }
  const std::string to_string() const;

  // useful methods
  int count(const T &element) const;
  int count_if(std::function<bool(T)> fn) const;
  Queue<T> filter(std::function<bool(T)> fn) const;
  void clear();
  static void swap(Queue<T> &a, Queue<T> &b);
  void reverse();
  Queue<T> reversed() const;
  void remove_duplicates();

  // min/max find
  QueueNode<T> *max() const;
  QueueNode<T> *max(std::function<int(T)> fn) const;
  QueueNode<T> *max_if(std::function<bool(T)> fn) const;
  QueueNode<T> *min() const;
  QueueNode<T> *min(std::function<int(T)> fn) const;
  QueueNode<T> *min_if(std::function<bool(T)> fn) const;

  // iterators
  inline QueueIterator<T> begin() const { return QueueIterator<T>(this->head); }
  inline QueueIterator<T> end() const { return QueueIterator<T>(this->tail); }

  // compare methods
  bool operator>(const Queue<T> &other) const;
  bool operator<(const Queue<T> &other) const;
  bool operator==(const Queue<T> &other) const;
  bool operator!=(const Queue<T> &other) const;
};

//----------
// Constructors
// ----------

// Vector based constructor
template <typename T>
Queue<T>::Queue(std::vector<T> vec) : head(nullptr), tail(nullptr), length(0) {
  for (const T &element : vec)
    this->enqueue(element);
}

// Based on range vector iterator constructor
template <typename T>
template <typename Iterator>
Queue<T>::Queue(Iterator begin, Iterator end)
    : head(nullptr), tail(nullptr), length(0) {
  if (begin >= end)
    throw std::invalid_argument(
        "The first iterator must be less than the second iterator!");

  for (Iterator it = begin; it != end; ++it)
    this->enqueue(*it);
}

// Copy constructor (deep copy)
template <typename T>
Queue<T>::Queue(const Queue<T> &other)
    : head(nullptr), tail(nullptr), length(0) {
  if (other.is_empty()) {
    this->head = this->tail = nullptr;
    return;
  }

  QueueNode<T> *temp = other.head;
  while (temp != nullptr) {
    this->enqueue(temp->data);
    temp = temp->next;
  }
}

// ---------
// Methods
// ---------

// Enqueue element in the queue
template <typename T> void Queue<T>::enqueue(const T &element) {
  QueueNode<T> *add = new QueueNode<T>(element);
  ++this->length;

  if (this->is_empty()) {
    this->head = this->tail = add;
    return;
  }

  this->tail = this->tail->next = add;
}

// Insert element at given iterator
template <typename T>
void Queue<T>::insert(const QueueIterator<T> qit, const T &element) {
  QueueNode<T> *target = qit.get_node();
  ++this->length;

  if (!this->head || this->head == target) {
    QueueNode<T> *add = new QueueNode<T>(element);
    add->next = this->head;
    this->head = add;

    if (!this->tail)
      this->tail = add;

    return;
  }

  QueueNode<T> *prev = nullptr, *current = this->head;

  while (current != nullptr && current != target) {
    prev = current;
    current = current->next;
  }

  if (current == target) {
    QueueNode<T> *add = new QueueNode<T>(element);
    prev->next = add;
    add->next = target;
  }
}

// Insert vector at given iterator
template <typename T>
void Queue<T>::insert(const QueueIterator<T> qit, const std::vector<T> &vec) {
  if (vec.empty())
    throw std::invalid_argument("Empty vector cannot be inserted!");

  QueueNode<T> *target = qit.get_node();

  if (!this->head || this->head == target) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
      QueueNode<T> *add = new QueueNode<T>(*it);
      add->next = this->head;
      this->head = add;

      if (!this->tail)
        this->tail = add;

      ++this->length;
    }

    return;
  }

  QueueNode<T> *prev = nullptr, *current = this->head;

  while (current != nullptr && current != target) {
    prev = current;
    current = current->next;
  }

  if (current == target) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
      QueueNode<T> *add = new QueueNode<T>(*it);
      prev->next = add;
      prev = add;

      ++this->length;
    }

    prev->next = target;
  }
}

// Dequeue element in the queue
template <typename T> T Queue<T>::dequeue() {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  QueueNode<T> *temp = this->head;
  T element = this->head->data;
  this->head = temp->next;

  delete temp;
  --this->length;

  return element;
}

// Erase specific element from the queue
template <typename T> void Queue<T>::erase(const T &element) {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  if (!this->contains(element))
    throw std::invalid_argument("Element was not found!");

  if (this->head->data == element) {
    this->dequeue();
    return;
  }

  --this->length;

  if (this->tail->data == element) {
    QueueNode<T> *temp = this->head;
    while (temp->next->next != nullptr)
      temp = temp->next;

    delete temp->next;
    temp->next = nullptr;

    return;
  }

  QueueNode<T> *temp1 = this->head, *temp2 = this->head->next;

  while (temp2 != nullptr && temp2->data != element) {
    temp2 = temp2->next;
    temp1 = temp1->next;
  }

  temp1->next = temp2->next;
  delete temp2;
}

// Erase element by iterator
template <typename T> void Queue<T>::erase(const QueueIterator<T> qit) {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  QueueNode<T> *target = qit.get_node();
  --this->length;

  if (this->head == target) {
    this->head = head->next;
    delete target;

    if (!this->head)
      this->tail = nullptr;

    return;
  }

  QueueNode<T> *prev = nullptr, *current = this->head;
  while (current != nullptr && current != target) {
    prev = current;
    current = current->next;
  }

  if (current == target) {
    prev->next = current->next;
    if (current == tail)
      this->tail = prev;

    delete current;
  }
}

// Erase all elements from the queue
template <typename T> void Queue<T>::erase_all(const T &element) {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  if (!this->contains(element))
    throw std::invalid_argument("Element was not found!");

  while (this->head && this->head->data == element)
    this->head = this->head->next;

  QueueNode<T> *temp1 = this->head, *temp2 = nullptr;

  while (temp1 != nullptr) {
    if (temp1->data == element) {
      temp2->next = temp1->next;
      --this->length;
    } else
      temp2 = temp1;

    temp1 = temp1->next;
  }
}

// Get index of a node (first occurence)
template <typename T> int Queue<T>::get_index(const QueueNode<T> *node) const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  int index = 0;
  QueueNode<T> *temp = this->head;
  while (temp != nullptr) {
    if (temp == node)
      break;

    temp = temp->next;
    index++;
  }

  return index;
}

// Get index of a value (first occurence)
template <typename T> int Queue<T>::get_index(const T &element) const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  int index = 0;
  QueueNode<T> *temp = this->head;
  while (temp != nullptr) {
    if (temp->data == element)
      break;

    temp = temp->next;
    index++;
  }

  return index;
}

// Get node by index
template <typename T> QueueNode<T> *Queue<T>::at(const int &index) const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  if (index < 0 || index > this->get_length() - 1)
    throw std::out_of_range("Provided index is out of range!");

  int idx = index;
  QueueNode<T> *temp = this->head;
  while (idx > 0) {
    temp = temp->next;
    --idx;
  }

  return temp;
}

// Equal operator
template <typename T> Queue<T> &Queue<T>::operator=(const Queue<T> &other) {
  if (this == &other)
    return *this;

  this->clear();

  QueueNode<T> *temp = other.head;
  while (temp != nullptr) {
    this->enqueue(temp->data);
    temp = temp->next;
  }

  return *this;
}

// If element is in the array
template <typename T> bool Queue<T>::contains(const T &element) const {
  QueueNode<T> *temp = this->head;
  while (temp != nullptr) {
    if (temp->data == element)
      return true;

    temp = temp->next;
  }

  return false;
}

// Find element in the queue
template <typename T> QueueIterator<T> Queue<T>::find(const T &element) const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  for (QueueIterator<T> qit = begin(); qit != end().get_node()->next; ++qit) {
    if (*qit == element)
      return QueueIterator<T>(qit, true);
  }

  return end();
}

// Find all elements in the queue
template <typename T>
std::vector<QueueIterator<T>> Queue<T>::find_all(const T &element) const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  std::vector<QueueIterator<T>> iterators;
  for (QueueIterator<T> qit = begin(); qit != end().get_node()->next; ++qit) {
    if (*qit == element)
      iterators.push_back(qit);
  }

  return iterators;
}

// Find all elements that satisfy the condition/predicate
template <typename T>
std::vector<QueueIterator<T>>
Queue<T>::find_if(std::function<bool(T)> fn) const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  std::vector<QueueIterator<T>> iterators;
  for (QueueIterator<T> qit = begin(); qit != end().get_node()->next; ++qit) {
    if (fn(*qit))
      iterators.push_back(qit);
  }

  return iterators;
}

// Replace first occurrence of a given element
template <typename T>
void Queue<T>::replace(const T &element, const T &replace) {
  QueueIterator<T> el = this->find(element);
  if (el == end())
    throw std::invalid_argument("Element was not found!");

  *el = replace;
}

// Replace at given iterator
template <typename T>
void Queue<T>::replace(const QueueIterator<T> qit, const T &replace) {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  *qit = replace;
}

// Replace all occurrences of element
template <typename T>
void Queue<T>::replace_all(const T &element, const T &replace) {
  std::vector<QueueIterator<T>> items = this->find_all(element);
  if (items.size() == 0)
    throw std::invalid_argument("Elements were not found!");

  for (QueueIterator<T> qit : items)
    *qit = replace;
}

// Replace all occurrences of element that satisfy the condition
template <typename T>
void Queue<T>::replace_if(std::function<bool(T)> fn, const T &replace) {
  std::vector<QueueIterator<T>> items = this->find_if(fn);
  for (QueueIterator<T> qit : items)
    *qit = replace;
}

// Replace all elements in a ragne
template <typename T>
void Queue<T>::replace_range(const QueueIterator<T> qit1,
                             const QueueIterator<T> qit2, const T &replace) {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  int index1 = this->get_index(qit1.get_node()),
      index2 = this->get_index(qit2.get_node());

  if (index1 > index2)
    throw std::invalid_argument("1st range should be less than 2nd!");

  for (QueueIterator<T> qit = qit1; qit != qit2; ++qit)
    *qit = replace;

  *qit2 = replace;
}

// To vector
template <typename T> const std::vector<T> Queue<T>::to_vector() const {
  std::vector<T> vec;
  QueueNode<T> *temp = this->head;

  while (temp != nullptr) {
    vec.push_back(temp->data);
    temp = temp->next;
  }

  return vec;
}

// To string
template <typename T> const std::string Queue<T>::to_string() const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  std::stringstream ss;
  QueueNode<T> *temp = this->head;

  while (temp != nullptr) {
    ss << temp->data;
    if (temp->next != nullptr)
      ss << " -> ";

    temp = temp->next;
  }

  return ss.str();
}

// ---------
// Useful methods
// ---------

// Clear queue
template <typename T> void Queue<T>::clear() {
  while (!this->is_empty())
    this->dequeue();

  this->tail = nullptr;
}

// Swapping two queues
template <typename T> void Queue<T>::swap(Queue<T> &a, Queue<T> &b) {
  Queue<T> temp = a;
  a = b;
  b = temp;
}

// Count element in the queue
template <typename T> int Queue<T>::count(const T &element) const {
  int count = 0;
  QueueNode<T> *temp = this->head;

  while (temp != nullptr) {
    if (temp->data == element)
      ++count;

    temp = temp->next;
  }

  return count;
}

// Count element in the queue by predicate
template <typename T> int Queue<T>::count_if(std::function<bool(T)> fn) const {
  int count = 0;
  QueueNode<T> *temp = this->head;

  while (temp != nullptr) {
    if (fn(temp->data))
      ++count;

    temp = temp->next;
  }

  return count;
}

// Filter elements in the queue
template <typename T>
Queue<T> Queue<T>::filter(std::function<bool(T)> fn) const {
  Queue<T> result;
  QueueNode<T> *temp = this->head;

  while (temp != nullptr) {
    if (fn(temp->data))
      result.enqueue(temp->data);

    temp = temp->next;
  }

  return result;
}

// Reverse a list
template <typename T> void Queue<T>::reverse() {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  QueueNode<T> *temp = nullptr, *prev = nullptr, *current = this->head;

  while (current != nullptr) {
    temp = current->next;
    current->next = prev;
    prev = current;
    current = temp;
  }

  this->head = prev;
}

// Return a reversed list
template <typename T> Queue<T> Queue<T>::reversed() const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  Queue<T> result;
  QueueNode<T> *temp = this->head;

  while (temp != nullptr) {
    QueueNode<T> *add = new QueueNode<T>(temp->data);
    if (result.is_empty()) {
      result.head = result.tail = add;
    } else {
      add->next = result.head;
      result.head = add;
    }

    ++result.length;
    temp = temp->next;
  }

  return result;
}

// Remove duplicates from queue
template <typename T> void Queue<T>::remove_duplicates() {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  QueueNode<T> *temp1 = this->head, *temp2, *duplicate;

  while (temp1 != nullptr && temp1->next != nullptr) {
    temp2 = temp1;

    while (temp2->next != nullptr) {
      if (temp1->data == temp2->next->data) {
        duplicate = temp2->next;
        temp2->next = temp2->next->next;
        delete duplicate;
      } else
        temp2 = temp2->next;
    }

    temp1 = temp1->next;
  }
}

//----------
// Min/max
// ----------

// Find max element
template <typename T> QueueNode<T> *Queue<T>::max() const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  QueueNode<T> *temp = this->head;
  QueueNode<T> *max = this->head;

  while (temp != nullptr) {
    if (max->data < temp->data)
      max = temp;

    temp = temp->next;
  }

  return max;
}

// Find max element by key
template <typename T>
QueueNode<T> *Queue<T>::max(std::function<int(T)> fn) const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  QueueNode<T> *temp = this->head;
  QueueNode<T> *max = this->head;

  while (temp != nullptr) {
    if (fn(max->data) < fn(temp->data))
      max = temp;

    temp = temp->next;
  }

  return max;
}

// Find max element by predicate
template <typename T>
QueueNode<T> *Queue<T>::max_if(std::function<bool(T)> fn) const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  bool found = false;
  QueueNode<T> *temp = this->head, *max;

  while (temp != nullptr) {
    if (fn(temp->data)) {
      if (!found || max->data < temp->data) {
        max = temp;
        found = true;
      }
    }

    temp = temp->next;
  }

  if (!found)
    throw std::runtime_error("Nothing was found by the given predicate!");

  return max;
}

// Find min element
template <typename T> QueueNode<T> *Queue<T>::min() const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  QueueNode<T> *temp = this->head;
  QueueNode<T> *min = this->head;

  while (temp != nullptr) {
    if (min->data > temp->data)
      min = temp;

    temp = temp->next;
  }

  return min;
}

// Find min element by key
template <typename T>
QueueNode<T> *Queue<T>::min(std::function<int(T)> fn) const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  QueueNode<T> *temp = this->head;
  QueueNode<T> *min = this->head;

  while (temp != nullptr) {
    if (fn(min->data) > fn(temp->data))
      min = temp;

    temp = temp->next;
  }

  return min;
}

// Find min element by predicate
template <typename T>
QueueNode<T> *Queue<T>::min_if(std::function<bool(T)> fn) const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  bool found = false;
  QueueNode<T> *temp = this->head, *min;

  while (temp != nullptr) {
    if (fn(temp->data)) {
      if (!found || min->data > temp->data) {
        min = temp;
        found = true;
      }
    }

    temp = temp->next;
  }

  if (!found)
    throw std::runtime_error("Nothing was found by the given predicate!");

  return min;
}

// ---------
// Compare
// ---------

// Greater than
template <typename T> bool Queue<T>::operator>(const Queue<T> &other) const {
  if (this->get_length() > other.get_length())
    return true;

  if (this->get_length() < other.get_length())
    return false;

  int count = 0;
  QueueNode<T> *temp1 = this->head, *temp2 = other.head;

  while (temp1 != nullptr && temp2 != nullptr) {
    if (temp1->data > temp2->data)
      count++;

    temp1 = temp1->next;
    temp2 = temp2->next;
  }

  return count == this->get_length();
}

// Less than
template <typename T> bool Queue<T>::operator<(const Queue<T> &other) const {
  if (this->get_length() < other.get_length())
    return true;

  if (this->get_length() > other.get_length())
    return false;

  int count = 0;
  QueueNode<T> *temp1 = this->head, *temp2 = other.head;

  while (temp1 != nullptr && temp2 != nullptr) {
    if (temp1->data < temp2->data)
      count++;

    temp1 = temp1->next;
    temp2 = temp2->next;
  }

  return count == this->get_length();
}

// Equal to
template <typename T> bool Queue<T>::operator==(const Queue<T> &other) const {
  if (this->get_length() != other.get_length())
    return false;

  QueueNode<T> *temp1 = this->head, *temp2 = other.head;

  while (temp1 != nullptr && temp2 != nullptr) {
    if (temp1->data != temp2->data)
      return false;

    temp1 = temp1->next;
    temp2 = temp2->next;
  }

  return true;
}

// Not equal to
template <typename T> bool Queue<T>::operator!=(const Queue<T> &other) const {
  return !(*this == other);
}

#endif
