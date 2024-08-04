#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>
#include <vector>

// Node class

template <class T> class Node {
public:
  T data;
  Node<T> *next;
  Node(const T &data) : data(data), next(nullptr) {}
};

// Queue on linked list

template <class T> class Queue {
private:
  Node<T> *head;
  Node<T> *tail;

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
  inline Node<T> *get_head() const { return this->head; }
  inline Node<T> *get_tail() const { return this->tail; }
  int get_length() const;
  int get_index(const T &element) const;

  // bool methods
  inline bool is_empty() const { return this->head == nullptr; }

  // enqueue/dequeue
  void enqueue(const T &element);
  T dequeue();

  // useful methods
  void clear();

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

  Node<T> *temp = other.head;
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
  Node<T> *add = new Node<T>(element);
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

  Node<T> *temp = this->head;
  T element = this->head->data;
  this->head = temp->next;

  delete temp;
  return element;
}

// Get length of the queue
template <typename T> int Queue<T>::get_length() const {
  int length = 0;
  Node<T> *temp = this->head;
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
  Node<T> temp = this->head;
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

  Node<T> *temp = other.head;
  while (temp != nullptr) {
    this->enqueue(temp->data);
    temp = temp->next;
  }

  return *this;
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
  Node<T> *temp1 = this->head, *temp2 = other.head;

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
  Node<T> *temp1 = this->head, *temp2 = other.head;

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

  Node<T> *temp1 = this->head, *temp2 = other.head;

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
