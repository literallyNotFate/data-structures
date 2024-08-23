#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

// Doubly linked list node

template <class T> class ListNode {
public:
  T data;
  ListNode<T> *next;
  ListNode<T> *prev;
  ListNode(const T &data) : next(nullptr), prev(nullptr), data(data) {};
};

// Doubly linked list

template <class T> class LinkedList {
private:
  ListNode<T> *head;
  ListNode<T> *tail;
  int length;

public:
  // constructors
  inline explicit LinkedList<T>() : head(nullptr), tail(nullptr), length(0){};
  LinkedList<T>(int size, const T &value);
  LinkedList<T>(const std::vector<T> &vec);
  template <typename Iterator> LinkedList<T>(Iterator begin, Iterator end);
  LinkedList<T>(const LinkedList<T> &other);

  // destructor
  inline ~LinkedList<T>() { this->clear(); }

  // equal operator
  LinkedList<T> &operator=(const LinkedList<T> &other);

  // getters
  inline ListNode<T> *get_head() const { return this->head; }
  inline ListNode<T> *get_tail() const { return this->tail; }
  inline int get_length() const { return this->length; }

  // bool methods
  inline bool is_empty() const { return this->head == nullptr; }

  // adding to the list
  void push_end(const T &element);
  void push_begin(const T &element);
  void push_after(const ListNode<T> *node, const T &element);
  void push_before(const ListNode<T> *node, const T &element);
  void push_index(const int index, const T &element);
  void push_random(const T &element);
  void push_middle(const T &element);
  void push_vector(const int index, const std::vector<T> &vec);

  // erasing from the list
  inline void remove_end() { this->remove_node(this->tail); };
  void remove_begin();
  void remove_node(const ListNode<T> *node);

  // converting methods
  const std::vector<T> to_vector(const bool order = true) const;
  static inline LinkedList<T> from_vector(const std::vector<T> &vec) {
    return LinkedList<T>(vec);
  }
  const std::string to_string(const bool order = true) const;

  // useful methods
  void clear();

  // compare methods
  bool operator>(const LinkedList<T> &other) const;
  bool operator<(const LinkedList<T> &other) const;
  bool operator==(const LinkedList<T> &other) const;
  bool operator!=(const LinkedList<T> &other) const;
};

// ---------
// Constructors
// ---------

// Fill constructor of a given size
template <typename T>
LinkedList<T>::LinkedList(int size, const T &value)
    : head(nullptr), tail(nullptr), length(0) {
  while (size > 0) {
    this->push_end(value);
    size--;
  }
}

// Vector based constructor
template <typename T>
LinkedList<T>::LinkedList(const std::vector<T> &vec)
    : head(nullptr), tail(nullptr), length(0) {
  for (const T &element : vec)
    this->push_end(element);
}

// Based on range vector iterator constructor
template <typename T>
template <typename Iterator>
LinkedList<T>::LinkedList(Iterator begin, Iterator end)
    : head(nullptr), tail(nullptr), length(0) {
  if (begin >= end)
    throw std::invalid_argument(
        "The first iterator must be less than the second iterator!");

  for (Iterator it = begin; it != end; ++it)
    this->push_end(*it);
}

// Copy constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other)
    : head(nullptr), tail(nullptr), length(0) {
  ListNode<T> *temp = other.head;
  while (temp != nullptr) {
    this->push_end(temp->data);
    temp = temp->next;
  }
}

// ---------
// Methods
// ---------

// Push element to the end
template <typename T> void LinkedList<T>::push_end(const T &element) {
  ListNode<T> *add = new ListNode<T>(element);
  ++this->length;

  if (this->is_empty()) {
    this->head = this->tail = add;
    return;
  }

  add->prev = this->tail;
  this->tail->next = add;

  this->tail = add;
}

// Push element to the beggining of a list
template <typename T> void LinkedList<T>::push_begin(const T &element) {
  ListNode<T> *add = new ListNode<T>(element);
  ++this->length;

  if (this->is_empty()) {
    this->head = this->tail = add;
    return;
  }

  add->next = this->head;
  this->head = this->head->prev = add;
}

// Push element after specific node
template <typename T>
void LinkedList<T>::push_after(const ListNode<T> *node, const T &element) {
  if (this->is_empty())
    throw std::length_error("List is empty!");

  if (node == nullptr)
    throw std::invalid_argument("Provided node is null!");

  ListNode<T> *add = new ListNode<T>(element);
  ListNode<T> *temp = this->head;

  while (temp != nullptr && temp != node)
    temp = temp->next;

  if (temp == nullptr)
    throw std::invalid_argument("Provided node was not found in the list!");

  add->next = temp->next;
  add->prev = temp;
  temp->next = add;

  ++this->length;

  if (temp == this->tail)
    this->tail = add;

  if (add->next != nullptr)
    add->next->prev = add;
}

// Push element before specific node
template <typename T>
void LinkedList<T>::push_before(const ListNode<T> *node, const T &element) {
  if (this->is_empty())
    throw std::length_error("List is empty!");

  if (node == nullptr)
    throw std::invalid_argument("Provided node is null!");

  ListNode<T> *add = new ListNode<T>(element);
  ListNode<T> *temp = this->head;

  while (temp != nullptr && temp != node)
    temp = temp->next;

  if (temp == nullptr)
    throw std::invalid_argument("Provided node was not found in the list!");

  add->prev = temp->prev;
  add->next = temp;

  ++this->length;

  if (temp->prev != NULL) {
    add->prev->next = add;
  } else {
    this->head = add;
  }

  temp->prev = add;
}

// Push element at given position (index)
template <typename T>
void LinkedList<T>::push_index(const int index, const T &element) {
  if (this->is_empty())
    throw std::length_error("List is empty!");

  if (index < 0 || index > this->length)
    throw std::out_of_range("Provided index is out of range!");

  ListNode<T> *add = new ListNode<T>(element);
  ListNode<T> *temp = this->head;

  if (index == 0) {
    this->push_begin(element);
    return;
  }

  if (index == this->length - 1) {
    this->push_end(element);
    return;
  }

  for (int i = 1; i < index && temp != nullptr; ++i)
    temp = temp->next;

  add->prev = temp;
  add->next = temp->next;
  temp->next = add;

  ++this->length;

  if (add->next != NULL)
    add->next->prev = add;
}

// Push element at the middle of a list
template <typename T> void LinkedList<T>::push_middle(const T &element) {
  if (this->is_empty()) {
    this->push_begin(element);
    return;
  }

  if (this->length == 1) {
    this->push_end(element);
    return;
  }

  ListNode<T> *add = new ListNode<T>(element);

  ListNode<T> *temp = head;
  for (size_t i = 0; i < (this->length - 1) / 2; ++i)
    temp = temp->next;

  add->next = temp->next;
  add->prev = temp;

  if (temp->next != nullptr)
    temp->next->prev = add;

  temp->next = add;

  if (temp == this->tail)
    this->tail = add;

  ++this->length;
}

// Push element at the random place
template <typename T> void LinkedList<T>::push_random(const T &element) {
  if (this->is_empty()) {
    this->push_begin(element);
    return;
  }

  static bool seed_initialized = false;
  if (!seed_initialized) {
    std::srand(static_cast<unsigned>(std::time(0)));
    seed_initialized = true;
  }

  this->push_index(std::rand() % this->length, element);
}

// Push vector at the given position
template <typename T>
void LinkedList<T>::push_vector(const int index, const std::vector<T> &vec) {
  if (this->is_empty())
    throw std::length_error("List is empty!");

  if (index < 0 || index > this->length - 1)
    throw std::out_of_range("Provided index is out of range!");

  int i = index;
  for (const T &element : vec) {
    this->push_index(i++, element);
  }
}

// Remove front
template <typename T> void LinkedList<T>::remove_begin() {
  if (this->is_empty())
    throw std::length_error("List is empty!");

  ListNode<T> *temp = this->head;
  this->head = temp->next;

  --this->length;
  delete temp;

  if (!this->is_empty())
    this->head->prev = nullptr;
}

// Remove provided node
template <typename T> void LinkedList<T>::remove_node(const ListNode<T> *node) {
  if (this->is_empty())
    throw std::length_error("List is empty!");

  if (node == nullptr)
    throw std::invalid_argument("Provided node is null!");

  if (this->head == node)
    this->head = node->next;

  if (this->tail == node)
    this->tail = node->prev;

  if (node->next != nullptr)
    node->next->prev = node->prev;

  if (node->prev != nullptr)
    node->prev->next = node->next;

  --this->length;
  delete node;
}

// Equal operator
template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other) {
  if (this != &other) {
    this->clear();

    ListNode<T> *temp = other.head;
    while (temp != nullptr) {
      this->push_end(temp->data);
      temp = temp->next;
    }
  }

  return *this;
}

// To vector
template <typename T>
const std::vector<T> LinkedList<T>::to_vector(const bool order) const {
  std::vector<T> vec;
  ListNode<T> *temp = order ? this->head : this->tail;

  while (temp != nullptr) {
    vec.push_back(temp->data);
    temp = order ? temp->next : temp->prev;
  }

  return vec;
}

// To string
template <typename T>
const std::string LinkedList<T>::to_string(const bool order) const {
  if (this->is_empty())
    throw std::length_error("Queue is empty!");

  std::stringstream ss;
  ListNode<T> *temp = order ? this->head : this->tail;

  while (temp != nullptr) {
    ss << temp->data;
    if ((order ? temp->next : temp->prev) != nullptr)
      ss << " <-> ";

    temp = order ? temp->next : temp->prev;
  }

  return ss.str();
}

// ---------
// Useful Methods
// ---------

// Clear all items in the linked list
template <typename T> void LinkedList<T>::clear() {
  ListNode<T> *current = this->head;

  while (current != nullptr) {
    ListNode<T> *next = current->next;
    --this->length;

    delete current;
    current = next;
  }

  this->head = this->tail = nullptr;
}

// ---------
// Compare
// ---------

// Greater than
template <typename T>
bool LinkedList<T>::operator>(const LinkedList<T> &other) const {
  if (this->length > other.length)
    return true;

  if (this->length < other.length)
    return false;

  int count = 0;
  ListNode<T> *temp1 = this->head, *temp2 = other.head;

  while (temp1 != nullptr && temp2 != nullptr) {
    if (temp1->data > temp2->data)
      count++;

    temp1 = temp1->next;
    temp2 = temp2->next;
  }

  return count == this->length;
}

// Less than
template <typename T>
bool LinkedList<T>::operator<(const LinkedList<T> &other) const {
  if (this->length < other.length)
    return true;

  if (this->length > other.length)
    return false;

  int count = 0;
  ListNode<T> *temp1 = this->head, *temp2 = other.head;

  while (temp1 != nullptr && temp2 != nullptr) {
    if (temp1->data < temp2->data)
      count++;

    temp1 = temp1->next;
    temp2 = temp2->next;
  }

  return count == this->length;
}

// Equal to
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &other) const {
  if (this->length != other.length)
    return false;

  ListNode<T> *temp1 = this->head, *temp2 = other.head;

  while (temp1 != nullptr && temp2 != nullptr) {
    if (temp1->data != temp2->data)
      return false;

    temp1 = temp1->next;
    temp2 = temp2->next;
  }

  return true;
}

// Not equal to
template <typename T>
bool LinkedList<T>::operator!=(const LinkedList<T> &other) const {
  return !(*this == other);
}

#endif
