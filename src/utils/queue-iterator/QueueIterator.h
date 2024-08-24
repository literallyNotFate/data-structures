#ifndef QUEUEITERATOR_H
#define QUEUEITERATOR_H

#include <iostream>
#include <stdexcept>

template <typename T> struct QueueNode;
template <typename T> class Queue;

// Queue Iterator (singly linked list)

template <class T> class QueueIterator {
private:
  QueueNode<T> *node;
  bool found;

public:
  // constructors
  inline QueueIterator<T>(const Queue<T> &queue)
      : node(queue.get_head()), found(false){};
  inline QueueIterator<T>(QueueNode<T> *node, const bool found = false)
      : node(node), found(found){};
  inline QueueIterator<T>(const QueueIterator<T> &qit, const bool found = false)
      : node(qit.node), found(found){};

  // getters
  inline QueueNode<T> *get_node() const { return this->node; }

  // increment operator
  inline QueueIterator<T> &operator++() {
    if (this->node != nullptr)
      this->node = this->node->next;

    return *this;
  }

  // get operator
  inline T &operator*() const { return this->node->data; }
  inline T *operator->() const { return &(this->node->data); }

  // adding operation
  inline QueueIterator<T> operator+(const int &value) const {
    if (value < 0)
      throw std::invalid_argument("Position argument should not be < 0!");

    int n = value;
    QueueNode<T> *temp = this->node;
    while (n-- && temp->next != nullptr)
      temp = temp->next;

    return QueueIterator<T>(temp);
  }

  // advance method
  inline static void advance(QueueIterator<T> &it, int pos) {
    if (pos < 0)
      throw std::invalid_argument("Position argument should not be < 0!");

    while (pos-- && it.node->next != nullptr)
      it.node = it.node->next;
  };

  // equals to
  inline bool operator==(const QueueIterator<T> &other) const {
    return this->node == other.node && this->found == other.found;
  }

  // not equals to
  inline bool operator!=(const QueueIterator<T> &other) const {
    return !(*this == other);
  }
};

#endif
