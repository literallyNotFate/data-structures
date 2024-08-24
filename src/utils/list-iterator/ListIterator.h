#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include <iostream>
#include <stdexcept>

template <typename T> struct ListNode;
template <typename T> class LinkedList;

// List Iterator (doubly linked list)

template <class T> class ListIterator {
private:
  ListNode<T> *node;
  bool found;

public:
  // constructors
  inline ListIterator<T>(const LinkedList<T> &list)
      : node(list.get_head()), found(false){};
  inline ListIterator<T>(ListNode<T> *node, const bool found = false)
      : node(node), found(found){};
  inline ListIterator<T>(const ListIterator<T> &lit, const bool found = false)
      : node(lit.node), found(found){};

  // getters
  inline ListNode<T> *get_node() const { return this->node; }

  // increment operators
  inline ListIterator<T> &operator++() {
    if (node)
      node = node->next;

    return *this;
  }

  inline ListIterator<T> &operator++(int) {
    ListIterator<T> temp = *this;
    ++(*this);
    return temp;
  }

  // decrement operators
  inline ListIterator<T> &operator--() {
    if (node)
      node = node->prev;

    return *this;
  }

  inline ListIterator<T> &operator--(int) {
    ListIterator<T> temp = *this;
    --(*this);
    return temp;
  }

  // get operators
  inline T &operator*() const {
    if (this->node == nullptr)
      throw std::out_of_range("Iterator is out of range");

    return this->node->data;
  }

  inline T *operator->() const {
    if (this->node == nullptr)
      throw std::out_of_range("Iterator is out of range");

    return &(this->node->data);
  }

  // adding operation
  inline ListIterator<T> operator+(const int &value) const {
    if (value < 0)
      throw std::invalid_argument("Position argument should not be < 0!");

    int n = value;
    ListNode<T> *temp = this->node;
    while (n-- && temp->next != nullptr)
      temp = temp->next;

    return ListIterator<T>(temp);
  }

  // substraction operation
  inline ListIterator<T> operator-(const int &value) const {
    if (value < 0)
      throw std::invalid_argument("Position argument should not be < 0!");

    int n = value;
    ListNode<T> *temp = this->node;
    while (n-- && temp->prev != nullptr)
      temp = temp->prev;

    return ListIterator<T>(temp);
  }

  // advance method
  inline static void advance(ListIterator<T> &lit, int n) {
    if (n > 0) {
      for (int i = 0; i < n; ++i) {
        if (lit.node == nullptr || lit.node->next == nullptr)
          return;

        lit.node = lit.node->next;
      }
    } else {
      for (int i = 0; i < -n; ++i) {
        if (lit.node == nullptr || lit.node->prev == nullptr)
          return;

        lit.node = lit.node->prev;
      }
    }
  }

  // equals to
  inline bool operator==(const ListIterator<T> &other) const {
    return this->node == other.node && this->found == other.found;
  }

  // not equals to
  inline bool operator!=(const ListIterator<T> &other) const {
    return !(*this == other);
  }
};

#endif
