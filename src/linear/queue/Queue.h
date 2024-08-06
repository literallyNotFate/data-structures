#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>
#include <vector>

// QueueNode class

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

public:
  // constructors
  inline explicit Queue<T>() : head(nullptr), tail(nullptr){};
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
  int get_length() const;
  int get_index(const T &element) const;

  // bool methods
  inline bool is_empty() const { return this->head == nullptr; }
  bool contains(const T &element) const;

  // adding to the queue
  void enqueue(const T &element);
  T dequeue();

  // erasing from the queue
  void erase_all(const T &element);

  // useful methods
  void clear();
  static void swap(Queue<T> &a, Queue<T> &b);

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
Queue<T>::Queue(std::vector<T> vec) : head(nullptr), tail(nullptr) {
  for (const T &element : vec)
    this->enqueue(element);
}

// Based on range vector iterator constructor
template <typename T>
template <typename Iterator>
Queue<T>::Queue(Iterator begin, Iterator end) : head(nullptr), tail(nullptr) {
  if (begin >= end)
    throw std::invalid_argument(
        "The first iterator must be less than the second iterator!");

  for (Iterator it = begin; it != end; ++it)
    this->enqueue(*it);
}

// Copy constructor (deep copy)
template <typename T>
Queue<T>::Queue(const Queue<T> &other) : head(nullptr), tail(nullptr) {
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
  if (this->is_empty()) {
    this->head = this->tail = add;
    return;
  }

  this->tail = this->tail->next = add;
}

// Dequeue element in the queue
template <typename T> T Queue<T>::dequeue() {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  QueueNode<T> *temp = this->head;
  T element = this->head->data;
  this->head = temp->next;

  delete temp;
  return element;
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
    if (temp1->data == element)
      temp2->next = temp1->next;
    else
      temp2 = temp1;

    temp1 = temp1->next;
  }
}

// Get length of the queue
template <typename T> int Queue<T>::get_length() const {
  int length = 0;
  QueueNode<T> *temp = this->head;
  while (temp != nullptr) {
    ++length;
    temp = temp->next;
  }

  return length;
}

// Get index of an element (first occurence)
template <typename T> int Queue<T>::get_index(const T &element) const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  int index = 0;
  QueueNode<T> temp = this->head;
  while (temp != nullptr) {
    if (temp->data == element)
      break;

    temp = temp->next;
    index++;
  }

  return index;
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
