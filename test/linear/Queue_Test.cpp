#include <Queue.h>
#include <QueueIterator.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

// ----------
// Constructors test
// ----------

TEST(QueueConstructors, BasicConstructor) {
  Queue<int> q;
  EXPECT_EQ(q.get_head(), nullptr) << "Head should be nullptr!";
  EXPECT_EQ(q.get_tail(), nullptr) << "Tail should be nullptr!";
  EXPECT_EQ(q.get_length(), 0) << "Length should be 0!";
}

TEST(QueueConstructors, VectorBasedConstructor) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  Queue<int> q(vec);

  EXPECT_EQ(q.get_length(), vec.size())
      << "Queue length should be vector size!";

  int index = 0;
  QueueNode<int> *temp = q.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, vec[index]) << "Values should be equal!";
    index++;
    temp = temp->next;
  }
}

TEST(QueueConstructors, RangeBasedConstructor) {
  std::vector<int> vec{10, 20, 30, 40, 50};
  Queue<int> q(vec.begin() + 1, vec.end());

  EXPECT_EQ(q.get_length(), 4) << "Size should be 4!";

  int index = 1;
  QueueNode<int> *temp = q.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, vec[index]) << "Values should be equal!";
    index++;
    temp = temp->next;
  }

  EXPECT_THROW(Queue<int> q1(vec.end(), vec.begin()), std::invalid_argument)
      << "Should throw invalid_argument if first iterator is greater than the "
         "second!";
}

TEST(QueueConstructors, CopyConstructor) {
  std::vector<std::string> vec{"hello", "world"};
  Queue<std::string> q1(vec);

  Queue<std::string> q2(q1);

  EXPECT_EQ(q1.get_length(), q2.get_length())
      << "Length of the queues should be equal!";

  QueueNode<std::string> *temp1 = q1.get_head(), *temp2 = q2.get_head();
  while (temp1 != nullptr && temp2 != nullptr) {
    EXPECT_EQ(temp1->data, temp2->data) << "Values should be equal!";

    temp1 = temp1->next;
    temp2 = temp2->next;
  }

  EXPECT_EQ(temp1, nullptr) << "First queue should be fully traversed!";
  EXPECT_EQ(temp2, nullptr) << "Second queue should be fully traversed!";
}

TEST(QueueConstructors, Destructor) {
  std::vector<bool> vec{true, true, false, false, false};
  Queue<bool> q(vec);

  EXPECT_EQ(q.get_length(), 5) << "Size of the queue must be 5!";

  q.~Queue<bool>();

  EXPECT_EQ(q.get_length(), 0)
      << "Size of the queue after clearing should be 0!";
  EXPECT_TRUE(q.is_empty()) << "Queue must be empty!";
  EXPECT_EQ(q.get_head(), nullptr) << "Head must be pointing to the nullptr !";
  EXPECT_EQ(q.get_tail(), nullptr) << " Tail must be pointing to the nullptr !";
}

// ----------
// Modify queue tests
// ----------

TEST(QueueModify, Enqueue) {
  Queue<char> q;

  q.enqueue('a');
  q.enqueue('b');
  q.enqueue('c');

  std::vector<char> expected{'a', 'b', 'c'};

  EXPECT_EQ(q.get_length(), 3) << "Size of the queue must be 3!";
  EXPECT_EQ(q.get_head()->data, 'a') << "First element must be 'a'.";
  EXPECT_EQ(q.get_last(), 'c') << "Last element should be equal to 'c'.";

  int index = 0;
  QueueNode<char> *temp = q.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }
}

TEST(QueueModify, Dequeue) {
  Queue<char> q;

  q.enqueue('a');
  q.enqueue('b');
  q.enqueue('c');

  EXPECT_EQ(q.get_length(), 3) << "Size of the queue must be 3!";

  char deq = q.dequeue();
  EXPECT_EQ(deq, 'a') << "Dequeued element should be equal to 'a'.";
  EXPECT_EQ(q.get_length(), 2) << "Size of the queue must be 2!";

  deq = q.dequeue();
  EXPECT_EQ(deq, 'b') << "Dequeued element should be equal to 'b'.";
  EXPECT_EQ(q.get_length(), 1) << "Size of the queue must be 1!";

  deq = q.dequeue();
  EXPECT_EQ(deq, 'c') << "Dequeued element should be equal to 'c'.";
  EXPECT_EQ(q.get_length(), 0) << "Size of the queue must be 0!";

  EXPECT_THROW(deq = q.dequeue(), std::length_error)
      << "Should throw length_error if queue is empty!";
}

TEST(QueueModify, Insert) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  Queue<int> q(vec);

  QueueIterator<int> qit = q.begin() + 2;
  q.insert(qit, 99);

  EXPECT_EQ(q.get_length(), vec.size() + 1)
      << "Length of the queue must be equal to 6!";

  std::vector<int> expected{1, 2, 99, 3, 4, 5};
  QueueNode<int> *temp = q.get_head();
  int index = 0;
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }
}

TEST(QueueModify, InsertVector) {
  std::vector<int> vec{10, 20, 30, 40, 50};
  Queue<int> q(vec);

  QueueIterator<int> qit = q.begin();
  QueueIterator<int>::advance(qit, 4);

  std::vector<int> add{0, 0, 0, 0, 0};
  q.insert(qit, add);

  std::vector<int> expected{10, 20, 30, 40, 0, 0, 0, 0, 0, 50};

  EXPECT_EQ(q.get_length(), vec.size() + add.size())
      << "Final length of the queue must be result of sum between initial "
         "vector and adding vector!";

  int index = 0;
  QueueNode<int> *temp = q.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]);

    index++;
    temp = temp->next;
  }

  std::vector<int> empty;
  EXPECT_THROW(q.insert(qit, empty), std::invalid_argument)
      << "Should throw invalid_argument if added vector is empty!";
}

TEST(QueueModify, Erase) {
  std::vector<int> vec{5, 10, 15, 20};
  Queue<int> q(vec);

  int el = 15;
  q.erase(el);

  EXPECT_EQ(q.get_length(), vec.size() - 1)
      << "Length of the queue must be equal to 3!";

  int index = 0;
  std::vector<int> expected{5, 10, 20};
  QueueNode<int> *temp = q.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]);

    index++;
    temp = temp->next;
  }

  el = 99;
  EXPECT_THROW(q.erase(el), std::invalid_argument)
      << "Should throw invalid_argument if element was not found!";

  q.clear();
  EXPECT_THROW(q.erase(el), std::length_error)
      << "Should throw length_error if queue is empty!";
}

TEST(QueueModify, EraseIterator) {
  std::vector<std::string> vec{"a", "ab", "abc", "abcd", "abcde"};
  Queue<std::string> q(vec.begin(), vec.end());

  QueueIterator<std::string> qit = q.end();
  q.erase(qit);

  EXPECT_EQ(q.get_length(), vec.size() - 1)
      << "Length of the queue must be equal to 4!";

  int index = 0;
  std::vector<std::string> expected{"a", "ab", "abc", "abcd"};
  QueueNode<std::string> *temp = q.get_head();

  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]);

    index++;
    temp = temp->next;
  }

  q.clear();
  EXPECT_THROW(q.erase(qit), std::length_error)
      << "Should throw length_error if queue is empty!";
}

TEST(QueueModify, EraseAll) {
  std::vector<float> vec{1.0, 1.0, 2.0, 3.0, 2.0, 2.0, 4.5};
  Queue<float> q(vec.begin(), vec.end());

  std::vector<float> expected{1.0, 1.0, 3.0, 4.5};
  float el = 2.0;

  q.erase_all(el);
  EXPECT_EQ(q.get_length(), expected.size())
      << "Queue length should be equal to 4!";

  int index = 0;
  QueueNode<float> *temp = q.get_head();

  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]);
    ++index;
    temp = temp->next;
  }

  el = 10.0;
  EXPECT_THROW(q.erase_all(el), std::invalid_argument)
      << "Should throw invalid_argument if element was not found!";

  q.clear();
  EXPECT_THROW(q.erase_all(el), std::length_error)
      << "Should throw length_error if queue is empty!";
}

// ----------
// Iterators test
// ----------

TEST(QueueIterators, IteratorBegin) {
  std::vector<int> vec{5, 10, 15, 20, 25};
  Queue<int> q(vec);

  QueueIterator<int> qit = q.begin();
  EXPECT_EQ(*qit, 5) << "Begin iterator should be at the first element!";
}

TEST(QueueIterators, IteratorEnd) {
  std::vector<int> vec{5, 10, 15, 20, 25};
  Queue<int> q(vec);

  QueueIterator<int> qit = q.end();
  EXPECT_EQ(*qit, 25) << "End iterator should be pointing at the last element!";
}

// ----------
// Methods test
// ----------

TEST(QueueMethods, EqualOperator) {
  std::vector<float> vec{10.0, 20.0, 30.0};
  Queue<float> q1(vec.begin() + 1, vec.end());

  EXPECT_EQ(q1.get_length(), 2) << "Size of the queue must be 2!";

  Queue<float> q2;
  q2 = q1;

  EXPECT_EQ(q1.get_length(), q2.get_length())
      << "Sizes of q1 and q2 must be equal!";

  int index = 1;
  QueueNode<float> *temp = q2.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, vec[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }
}

TEST(QueueMethods, Contains) {
  std::vector<int> vec{1, 2, 3};
  Queue<int> q(vec);

  EXPECT_TRUE(q.contains(1)) << "1 should be in the array!";
  EXPECT_FALSE(q.contains(99)) << "99 should not be in the array!";
}

TEST(QueueMethods, At) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  Queue<int> q(vec);

  int index = 0;
  EXPECT_EQ(q.at(index)->data, *(q.begin())) << "First element should be 1!";

  index = 4;
  EXPECT_EQ(q[index]->data, *(q.end())) << "Last element should be 5!";

  index = 99;
  EXPECT_THROW(q.at(index), std::out_of_range)
      << "Should throw out_of_range if provided index is wrong!";

  q.clear();
  EXPECT_THROW(q.at(index), std::length_error)
      << "Should throw length_error if queue is empty!";
}

TEST(QueueMethods, Find) {
  std::vector<float> vec{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
  Queue<float> q(vec);

  QueueIterator<float> f = q.find(5.0);
  EXPECT_EQ(vec[q.get_index(*f)], vec[4]) << "Values should be equal!";

  f = q.find(7.0);
  EXPECT_EQ(vec[q.get_index(*f)], vec[vec.size() - 1])
      << "Values should be equal!";

  f = q.find(99.0);
  EXPECT_EQ(f, q.end()) << "Should point to the last element if not found!";

  q.clear();
  EXPECT_THROW(f = q.find(1.0), std::length_error)
      << "Should throw length_error if queue is empty!";
}

TEST(QueueMethods, FindAll) {
  std::vector<char> vec{'a', 'b', 'c', 'a', 'a', 'b'};
  Queue<char> q(vec.begin(), vec.end());

  std::vector<QueueIterator<char>> iterators{q.begin() + 1, q.end()};
  std::vector<QueueIterator<char>> f = q.find_all('b');

  for (int i = 0; i < f.size(); i++) {
    EXPECT_EQ(vec[q.get_index(*(f[i]))], vec[q.get_index(*iterators[i])])
        << "Values should be equal!";
    EXPECT_EQ(f[i], iterators[i]) << "Iterators should be equal!";
  }

  f = q.find_all('x');
  EXPECT_EQ(f.size(), 0) << "Vector of not found values must be 0!";

  q.clear();
  EXPECT_THROW(q.find_all('a'), std::length_error)
      << "Should throw length_error if queue is empty!";
}

TEST(QueueMethods, FindIf) {
  std::vector<int> vec{6, 7, 8, 9, 10};
  Queue<int> q(vec.begin(), vec.end());

  QueueIterator<int> qit = q.begin();
  std::vector<QueueIterator<int>> iterators{qit + 1, qit + 3};
  std::vector<QueueIterator<int>> f =
      q.find_if([](int x) { return x % 2 != 0; });

  for (int i = 0; i < f.size(); i++) {
    EXPECT_EQ(vec[q.get_index(*(f[i]))], vec[q.get_index(*iterators[i])])
        << "Values should be equal!";
    EXPECT_EQ(f[i], iterators[i]) << "Iterators should be equal!";
  }

  f = q.find_if([](int x) { return x < 0; });

  EXPECT_EQ(f.size(), 0) << "Vector of not found values must be 0!";

  q.clear();
  EXPECT_THROW(q.find_if([](int x) { return x > 0; }), std::length_error)
      << "Should throw length_error if queue is empty!";
}

TEST(QueueMethods, ReplaceOccurence) {
  std::vector<std::string> vec{"a", "ab", "abc", "abcd", "abcde"};
  Queue<std::string> q(vec);

  std::string find = "abc";
  std::vector<std::string> expected{"a", "ab", "hello", "abcd", "abcde"};

  q.replace(find, "hello");

  int index = 0;
  QueueNode<std::string> *temp = q.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  find = "x";
  EXPECT_THROW(q.replace(find, "a"), std::invalid_argument)
      << "Should throw invalid_argument if element was not found!";

  q.clear();
  EXPECT_THROW(q.replace(find, "a"), std::length_error)
      << "Should throw length_error if queue is empty!";
}

TEST(QueueMethods, ReplaceIterator) {
  std::vector<char> vec{'a', 'b', 'c', 'd', 'e'};
  Queue<char> q(vec);

  QueueIterator<char> qit = q.begin() + 3;
  std::vector<char> expected{'a', 'b', 'c', 'x', 'e'};

  q.replace(qit, 'x');

  int index = 0;
  QueueNode<char> *temp = q.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  q.clear();
  EXPECT_THROW(q.replace(qit, 'x'), std::length_error)
      << "Should throw length_error if queue is empty!";
}

TEST(QueueMethods, ReplaceAll) {
  std::vector<int> vec{2, 3, 4, 2, 5, 6, 2};
  Queue<int> q(vec);

  int replace = 2;
  std::vector<int> expected{99, 3, 4, 99, 5, 6, 99};

  q.replace_all(replace, 99);

  QueueNode<int> *temp = q.get_head();
  int index = 0;
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  replace = 50;
  EXPECT_THROW(q.replace_all(replace, 5), std::invalid_argument)
      << "Should throw invalid_argument if elements were not found!";

  q.clear();
  EXPECT_THROW(q.replace_all(replace, 5), std::length_error)
      << "Should throw length_error if queue is empty!";
}

TEST(QueueMethods, ReplaceIf) {
  std::vector<bool> vec{true, true, false, false, true, true};
  Queue<bool> q(vec.begin(), vec.end());

  std::vector<bool> expected(vec.size());
  std::fill(expected.begin(), expected.end(), true);

  q.replace_if([](bool x) { return x == false; }, true);

  QueueNode<bool> *temp = q.get_head();
  int index = 0;
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  q.clear();
  EXPECT_THROW(q.replace_if([](bool x) { return x == true; }, false),
               std::length_error)
      << "Should throw length_error if queue is empty!";
}

TEST(QueueMethods, ReplaceRange) {
  std::vector<char> vec{'a', 'b', 'c', 'd', 'e'};
  Queue<char> q(vec);

  QueueIterator<char> qit = q.begin();
  char replace = 'x';
  std::vector<char> expected{'a', 'b', 'x', 'x', 'x'};

  EXPECT_THROW(q.replace_range(qit + 2, qit + 1, replace),
               std::invalid_argument)
      << "qit1 should be less than qit2!";

  q.replace_range(qit + 2, q.end(), replace);

  int index = 0;
  QueueNode<char> *temp = q.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  q.clear();
  EXPECT_THROW(q.replace_range(q.begin(), q.end(), replace), std::length_error)
      << "Should throw length_error if queue is empty!";
}

// ----------
// Compare test
// ----------

TEST(QueueCompare, GreaterThan) {
  std::vector<float> vec1{1.2, 2.4, 4.6}, vec2{5.4, 4.7, 6.2};
  Queue<float> q1(vec1), q2(vec1.begin() + 1, vec1.end()), q3(vec2);

  EXPECT_TRUE(q1 > q2) << "q1 should be greater than q2, because of sizes!";

  EXPECT_FALSE(q1 > q1) << "Should return false because queues are equal!";
  EXPECT_FALSE(q1 > q3)
      << "Should return true because ALL values of q3 > ALL values of q1.";
}

TEST(QueueCompare, LessThan) {
  std::vector<float> vec1{1.2, 2.4, 4.6}, vec2{5.4, 4.7, 6.2};
  Queue<float> q1(vec1), q2(vec1.begin() + 1, vec1.end()), q3(vec2);

  EXPECT_TRUE(q2 < q1) << "q2 should be less than q1, because of sizes!";

  EXPECT_FALSE(q1 < q1) << "Should return false because arrays are equal!";
  EXPECT_FALSE(q3 < q1)
      << "Should return true because ALL values of q1 < ALL values of q3.";
}

TEST(QueueCompare, EqualityOperator) {
  std::vector<int> vec1{0, 0}, vec2{1, 1};
  Queue<int> q1(vec1), q2(vec1), q3(vec2);

  EXPECT_TRUE(q1 == q2) << "q1 and q2 should be equal!";
  EXPECT_FALSE(q1 == q3) << "q1 and q3 should not be equal!";
}

TEST(QueueCompare, InequalityOperator) {
  std::vector<int> vec1{0, 0}, vec2{1, 1};
  Queue<int> q1(vec1), q2(vec1), q3(vec2);

  EXPECT_FALSE(q1 != q2) << "q1 and q2 should not be unequal!";
  EXPECT_TRUE(q1 != q3) << "q1 and q3 should be unequal!";
}

// ----------
// Useful functions test
// ----------

TEST(QueueUsefulFunctions, Clear) {
  std::vector<bool> vec{true, true, false, false, false};
  Queue<bool> q(vec);

  EXPECT_EQ(q.get_length(), 5) << "Size of the queue must be 5!";

  q.clear();

  EXPECT_EQ(q.get_length(), 0)
      << "Size of the queue after clearing should be 0!";
  EXPECT_TRUE(q.is_empty()) << "Queue must be empty!";
  EXPECT_EQ(q.get_head(), nullptr) << "Head must be pointing to the nullptr!";
  EXPECT_EQ(q.get_tail(), nullptr) << " Tail must be pointing to the nullptr!";
}

TEST(QueueUsefulFunctions, Swap) {
  std::vector<int> vec1{1, 2, 3}, vec2{4, 5, 6, 7};
  Queue<int> q1(vec1), q2(vec2);

  EXPECT_EQ(q1.get_length(), vec1.size()) << "First queue should be sized 3!";
  EXPECT_EQ(q2.get_length(), vec2.size()) << "Second queue should be sized 4!";

  Queue<int>::swap(q1, q2);

  EXPECT_EQ(q1.get_length(), vec2.size())
      << "First queue after swapping should be sized 4!";
  EXPECT_EQ(q2.get_length(), vec1.size())
      << "Second queue after swapping should be sized 3!";

  QueueNode<int> *temp = q1.get_head();
  int index = 0;
  while (temp != NULL) {
    EXPECT_EQ(temp->data, vec2[index]) << "Values should be equal!";
    index++;
    temp = temp->next;
  }

  index = 0;
  temp = q2.get_head();
  while (temp != NULL) {
    EXPECT_EQ(temp->data, vec1[index]) << "Values should be equal!";
    index++;
    temp = temp->next;
  }
}
