#include <LinkedList.h>
#include <gtest/gtest.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// ----------
// Constructors test
// ----------

TEST(LinkedListConstructors, BasicConstructor) {
  LinkedList<int> l;

  EXPECT_EQ(l.get_head(), nullptr) << "Head should be nullptr!";
  EXPECT_EQ(l.get_tail(), nullptr) << "Tail should be nullptr!";
  EXPECT_EQ(l.get_length(), 0) << "Length should be 0!";
}

TEST(LinkedListConstructors, FillConstructor) {
  LinkedList<char> l(4, 'x');
  std::vector<char> expected{'x', 'x', 'x', 'x'};

  EXPECT_EQ(l.get_length(), expected.size()) << "Length should be equal to 4!";

  int index = 0;
  ListNode<char> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }
}

TEST(LinkedListConstructors, VectorBasedConstructor) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  LinkedList<int> l(vec);

  EXPECT_EQ(l.get_length(), vec.size()) << "List length should be vector size!";

  int index = 0;
  ListNode<int> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, vec[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }
}

TEST(LinkedListConstructors, RangeBasedConstructor) {
  std::vector<std::string> vec{"abc", "hello", "world", "string"};
  LinkedList<std::string> l(vec.begin() + 1, vec.end());

  EXPECT_EQ(l.get_length(), 3) << "Length should be 3!";

  int index = 1;
  ListNode<std::string> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, vec[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  EXPECT_THROW(LinkedList<std::string> l1(vec.end(), vec.begin()),
               std::invalid_argument)
      << "Should throw invalid_argument if first iterator is greater than the "
         "second!";
}

TEST(LinkedListConstructors, CopyConstructor) {
  std::vector<float> vec{6.7, 7.8, 8.9};
  LinkedList<float> l1(vec);

  LinkedList<float> l2(l1);

  EXPECT_EQ(l1.get_length(), l2.get_length())
      << "Length of the lists should be equal!";

  ListNode<float> *temp1 = l1.get_head(), *temp2 = l2.get_head();
  while (temp1 != nullptr && temp2 != nullptr) {
    EXPECT_EQ(temp1->data, temp2->data) << "Values should be equal!";

    temp1 = temp1->next;
    temp2 = temp2->next;
  }

  EXPECT_EQ(temp1, nullptr) << "First list should be fully traversed!";
  EXPECT_EQ(temp2, nullptr) << "Second list should be fully traversed!";
}

TEST(LinkedListConstructors, Destructor) {
  std::vector<bool> vec{true, false};
  LinkedList<bool> l(vec.begin(), vec.end());

  EXPECT_EQ(l.get_length(), 2) << "Length of the list must be 5!";

  l.~LinkedList<bool>();

  EXPECT_EQ(l.get_length(), 0)
      << "Length of the list after clearing should be 0!";
  EXPECT_TRUE(l.is_empty()) << "List must be empty!";
  EXPECT_EQ(l.get_head(), nullptr) << "Head must be pointing to the nullptr !";
  EXPECT_EQ(l.get_tail(), nullptr) << " Tail must be pointing to the nullptr !";
}

// ----------
// Modify list tests
// ----------

TEST(LinkedListModify, PushEnd) {
  LinkedList<int> l;

  l.push_end(1);
  l.push_end(2);
  l.push_end(3);

  std::vector<int> expected{1, 2, 3};

  EXPECT_EQ(l.get_length(), 3) << "Size of the list must be 3!";
  EXPECT_EQ(l.get_head()->data, 1) << "First element must be 1.";
  EXPECT_EQ(l.get_tail()->data, 3) << "Last element should be equal to 3.";

  int index = 0;
  ListNode<int> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }
}

TEST(LinkedListModify, PushBegin) {
  LinkedList<int> l;

  l.push_begin(1);
  l.push_begin(2);
  l.push_begin(3);

  std::vector<int> expected{3, 2, 1};

  EXPECT_EQ(l.get_length(), 3) << "Size of the list must be 3!";
  EXPECT_EQ(l.get_head()->data, 3) << "First element must be 3.";
  EXPECT_EQ(l.get_tail()->data, 1) << "Last element should be equal to 1.";

  int index = 0;
  ListNode<int> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }
}

TEST(LinkedListModify, RemoveEnd) {
  LinkedList<int> l;

  l.push_end(1);
  l.push_end(2);
  l.push_end(3);

  l.remove_end();
  std::vector<int> expected{1, 2};

  EXPECT_EQ(l.get_length(), 2) << "Size of the list must be 2!";
  EXPECT_EQ(l.get_head()->data, 1) << "First element must be 1.";
  EXPECT_EQ(l.get_tail()->data, 2) << "Last element should be equal to 2.";

  int index = 0;
  ListNode<int> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  l.clear();
  EXPECT_THROW(l.remove_end(), std::length_error)
      << "Should throw length_error if list is empty!";
}

TEST(LinkedListModify, RemoveBegin) {
  LinkedList<int> l;

  l.push_end(1);
  l.push_end(2);
  l.push_end(3);

  l.remove_begin();
  std::vector<int> expected{2, 3};

  EXPECT_EQ(l.get_length(), 2) << "Size of the list must be 2!";
  EXPECT_EQ(l.get_head()->data, 2) << "First element must be 2.";
  EXPECT_EQ(l.get_tail()->data, 3) << "Last element should be equal to 3.";

  int index = 0;
  ListNode<int> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  l.clear();
  EXPECT_THROW(l.remove_begin(), std::length_error)
      << "Should throw length_error if list is empty!";
}

TEST(LinkedListModify, RemoveNode) {
  LinkedList<int> l;

  l.push_end(5);
  l.push_end(3);
  l.push_end(7);
  l.push_begin(40);
  l.push_begin(20);

  ListNode<int> *node1 = l.get_head()->next->next->next;
  l.remove_node(node1);
  std::vector<int> expected{20, 40, 5, 7};

  EXPECT_EQ(l.get_length(), 4) << "Length of the list must be 4!";
  EXPECT_EQ(l.get_head()->data, 20) << "First element must be 20.";
  EXPECT_EQ(l.get_tail()->data, 7) << "Last element should be equal to 7.";

  int index = 0;
  ListNode<int> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  ListNode<int> *node2 = nullptr;
  EXPECT_THROW(l.remove_node(node2), std::invalid_argument)
      << "Should throw invalid_argument if node is equal to nullptr.";

  l.clear();
  EXPECT_THROW(l.remove_node(node1), std::length_error)
      << "Should throw length_error if list is empty!";
}

// ----------
// Methods test
// ----------

TEST(LinkedListMethods, EqualOperator) {
  std::vector<double> vec{1.2, 2.3, 3.4};
  LinkedList<double> l1(vec.begin(), vec.end());

  EXPECT_EQ(l1.get_length(), 3) << "Length of the list must be 3!";

  LinkedList<double> l2;
  l2 = l1;

  EXPECT_EQ(l1.get_length(), l2.get_length())
      << "Length values of l1 and l2 must be equal!";

  int index = 0;
  ListNode<double> *temp = l2.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, vec[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }
}

// ----------
// Compare test
// ----------

TEST(LinkedListCompare, GreaterThan) {
  std::vector<float> vec1{1.2, 2.4, 4.6}, vec2{5.4, 4.7, 6.2};
  LinkedList<float> l1(vec1), l2(vec1.begin() + 1, vec1.end()), l3(vec2);

  EXPECT_TRUE(l1 > l2) << "l1 should be greater than l2, because of lengths!";

  EXPECT_FALSE(l1 > l1) << "Should return false because lists are equal!";
  EXPECT_FALSE(l1 > l3)
      << "Should return true because ALL values of l3 > ALL values of l1.";
}

TEST(LinkedListCompare, LessThan) {
  std::vector<float> vec1{1.2, 2.4, 4.6}, vec2{5.4, 4.7, 6.2};
  LinkedList<float> l1(vec1), l2(vec1.begin() + 1, vec1.end()), l3(vec2);

  EXPECT_TRUE(l2 < l1) << "l2 should be less than l1, because of lengths!";

  EXPECT_FALSE(l1 < l1) << "Should return false because lists are equal!";
  EXPECT_FALSE(l3 < l1)
      << "Should return true because ALL values of l1 < ALL values of l3.";
}

TEST(LinkedListCompare, EqualityOperator) {
  std::vector<int> vec1{0, 0}, vec2{1, 1};
  LinkedList<int> l1(vec1), l2(vec1), l3(vec2);

  EXPECT_TRUE(l1 == l2) << "l1 and l2 should be equal!";
  EXPECT_FALSE(l1 == l3) << "l1 and l3 should not be equal!";
}

TEST(LinkedListCompare, InequalityOperator) {
  std::vector<int> vec1{0, 0}, vec2{1, 1};
  LinkedList<int> l1(vec1), l2(vec1), l3(vec2);

  EXPECT_FALSE(l1 != l2) << "l1 and l2 should not be equal!";
  EXPECT_TRUE(l1 != l3) << "l1 and l3 should not be equal!";
}

// ----------
// Useful functions test
// ----------

TEST(LinkedListUsefulFunctions, Clear) {
  std::vector<char> vec{'a', 'b', 'c'};
  LinkedList<char> l(vec);

  EXPECT_EQ(l.get_length(), 3) << "Length of list must be 3!";

  l.clear();

  EXPECT_EQ(l.get_length(), 0)
      << "Length of the list after clearing should be 0!";
  EXPECT_TRUE(l.is_empty()) << "List must be empty!";
  EXPECT_EQ(l.get_head(), nullptr) << "Head must be pointing to the nullptr!";
  EXPECT_EQ(l.get_tail(), nullptr) << " Tail must be pointing to the nullptr!";
}
