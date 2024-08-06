#include <Queue.h>
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
