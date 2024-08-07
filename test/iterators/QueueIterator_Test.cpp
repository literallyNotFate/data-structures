#include <Queue.h>
#include <QueueIterator.h>
#include <gtest/gtest.h>

#include <iostream>
#include <stdexcept>
#include <vector>

// ----------
// Constructor test
// ----------

TEST(QueueIteratorConstructors, BasicConstructor) {
  std::vector<int> vec{1, 2, 3, 4, 5, 6};
  Queue<int> q(vec);

  QueueIterator<int> qit(q);
  EXPECT_EQ(qit.get_node()->data, vec[0])
      << "Iterator should point to the first by default!";
}

// ----------
// Getter test
// ----------

TEST(QueueIteratorGetters, GetNode) {
  std::vector<int> vec{1, 2, 3};
  Queue<int> q(vec);

  QueueIterator<int> qit(q);
  EXPECT_NE(qit.get_node(), nullptr) << "Node should not be nullptr!";
}

// ----------
// Methods test
// ----------

TEST(QueueIteratorMethods, IncrementOperator) {
  std::vector<std::string> vec{"a", "ab", "abc", "abcd", "abcde"};
  Queue<std::string> q(vec);

  QueueIterator<std::string> qit(q);
  std::vector<std::string> expected{"a", "ab", "abc"};

  int n = 3, index = 0;
  while (n > 0) {
    EXPECT_EQ(qit.get_node()->data, expected[index])
        << "Values should be equal!";

    index++;
    ++qit;
    n--;
  }
}

TEST(QueueIteratorMethods, DereferenceOperator) {
  std::vector<float> vec{1.0, 2.0, 3.0, 4.0};
  Queue<float> q(vec);

  QueueIterator<float> qit(q);
  EXPECT_EQ(*qit, vec[0]) << "Iterator should be at 1st element";

  ++qit;
  EXPECT_EQ(*qit, vec[1]) << "Iterator should be at 2nd element";
}

TEST(QueueIteratorMethods, AdditionOperator) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  Queue<int> q(vec);

  QueueIterator<int> qit(q);
  auto qit2 = qit + 2;

  EXPECT_EQ(*qit2, 3) << "Value should be equal to 3!";

  qit2 = qit2 + 10;
  EXPECT_EQ(*qit2, vec[vec.size() - 1])
      << "Iterator should be at the last element!";

  EXPECT_THROW(qit2 + (-2), std::invalid_argument)
      << "Should throw invalid_argument exception if value is < 0!";
}

TEST(QueueIteratorMethods, Advance) {
  std::vector<char> vec{'a', 'b', 'c', 'd', 'e'};
  Queue<char> q(vec.begin(), vec.end());

  QueueIterator<char> qit(q);
  QueueIterator<char>::advance(qit, 2);

  EXPECT_EQ(*qit, 'c') << "Value should be equal to 'c'!";

  QueueIterator<char>::advance(qit, 100);
  EXPECT_EQ(*qit, vec[vec.size() - 1]) << "Value should be equal to 'e'!";

  EXPECT_THROW(QueueIterator<char>::advance(qit, -5), std::invalid_argument)
      << "Should throw invalid_argument if position is < 0!";
}

// ----------
// Compare test
// ----------

TEST(QueueIteratorCompare, EqualityOperator) {
  std::vector<int> vec{1, 2, 3};
  Queue<int> q(vec.begin(), vec.end());

  QueueIterator<int> qit1(q), qit2(q);

  EXPECT_TRUE(qit1 == qit2) << "Queue iterators qit1 and qit2 should be equal!";
}

TEST(QueueIteratorCompare, InequalityOperator) {
  std::vector<int> vec{1, 2, 3};
  Queue<int> q1(vec), q2(vec.begin() + 1, vec.end());

  QueueIterator<int> qit1(q1), qit2(q2);

  EXPECT_TRUE(qit1 != qit2)
      << "Queue iterators qit1 and qit2 should not be equal!";
}
