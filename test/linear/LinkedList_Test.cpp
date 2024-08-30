#include <LinkedList.h>
#include <gtest/gtest.h>

#include <algorithm>
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
  EXPECT_EQ(l.get_head(), nullptr) << "Head must be pointing to the nullptr!";
  EXPECT_EQ(l.get_tail(), nullptr) << " Tail must be pointing to the nullptr!";
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

TEST(LinkedListModify, PushAfter) {
  std::vector<double> vec{1.0, 2.0, 3.0, 4.0, 5.0};
  LinkedList<double> l(vec);

  ListNode<double> *node = l.get_tail();
  l.push_after(node, 50.0);

  EXPECT_EQ(l.get_length(), vec.size() + 1) << "Size of the list must be 6!";
  EXPECT_EQ(l.get_tail()->data, 50.0) << "Last element must be 50.0.";

  node = l.get_head()->next;
  l.push_after(node, 10.0);

  std::vector<double> expected{1.0, 2.0, 10.0, 3.0, 4.0, 5.0, 50.0};

  int index = 0;
  ListNode<double> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  ListNode<double> wrong(100.0);
  EXPECT_THROW(l.push_after(&wrong, 50.0), std::invalid_argument)
      << "Should throw invalid_argument if node was not found in the list!";

  node = nullptr;
  EXPECT_THROW(l.push_after(node, 50.0), std::invalid_argument)
      << "Should throw invalid_argument if node is null!";

  l.clear();
  EXPECT_THROW(l.push_after(&wrong, 50.0), std::length_error)
      << "Should throw length_error if list is empty!";
}

TEST(LinkedListModify, PushBefore) {
  std::vector<char> vec{'a', 'b', 'c'};
  LinkedList<char> l(vec);

  ListNode<char> *node = l.get_head();
  l.push_before(node, 'x');

  EXPECT_EQ(l.get_length(), vec.size() + 1) << "Size of the list must be 6!";
  EXPECT_EQ(l.get_head()->data, 'x') << "First element must be 'x'.";

  node = l.get_head()->next->next;
  l.push_before(node, 'y');

  std::vector<char> expected{'x', 'a', 'y', 'b', 'c'};

  int index = 0;
  ListNode<char> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  ListNode<char> wrong('d');
  EXPECT_THROW(l.push_before(&wrong, 'z'), std::invalid_argument)
      << "Should throw invalid_argument if node was not found in the list!";

  node = nullptr;
  EXPECT_THROW(l.push_before(node, 'z'), std::invalid_argument)
      << "Should throw invalid_argument if node is null!";

  l.clear();
  EXPECT_THROW(l.push_before(&wrong, 'z'), std::length_error)
      << "Should throw length_error if list is empty!";
}

TEST(LinkedListModify, PushIndex) {
  std::vector<int> vec{5, 6, 7, 8, 9, 10};
  LinkedList<int> l(vec.begin(), vec.end());

  int index = 0;
  l.push_index(index, 100);

  EXPECT_EQ(l.get_length(), vec.size() + 1) << "Size of the list must be 6!";

  index = 5;
  l.push_index(index, 50);

  index = 7;
  l.push_index(index, 200);

  std::vector<int> expected{100, 5, 6, 7, 8, 50, 9, 10, 200};

  index = 0;
  ListNode<int> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  index = 99;
  EXPECT_THROW(l.push_index(index, 100), std::out_of_range)
      << "Should throw out_of_range if provided index is not valid!";

  l.clear();
  EXPECT_THROW(l.push_index(index, 100), std::length_error)
      << "Should throw length_error if list is empty!";
}

TEST(LinkedListModify, PushMiddle) {
  std::vector<std::string> vec{"hello", "world"};
  LinkedList<std::string> l(vec.begin(), vec.end());

  l.push_middle("middle");

  std::vector<std::string> expected{"hello", "middle", "world"};

  int index = 0;
  ListNode<std::string> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }
}

TEST(LinkedListModify, PushRandom) {
  LinkedList<float> l;

  l.push_end(1.0);
  l.push_end(2.0);
  l.push_end(3.0);

  l.push_random(10.0);

  std::vector<float> expected = l.to_vector();
  EXPECT_EQ(l.get_length(), expected.size()) << "Size should be equal to 4!";

  int index = 0;
  ListNode<float> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }
}

TEST(LinkedListModify, PushVector) {
  std::vector<char> vec{'a', 'b', 'c', 'd', 'e'};
  LinkedList<char> l(vec.begin(), vec.end());

  std::vector<char> add{'x', 'y', 'z'};
  int index = 3;

  l.push_vector(index, add);
  EXPECT_EQ(l.get_length(), vec.size() + add.size())
      << "The resulting length should be equal to 8!";

  std::vector<char> expected{'a', 'b', 'c', 'x', 'y', 'z', 'd', 'e'};

  index = 0;
  ListNode<char> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  index = 99;
  EXPECT_THROW(l.push_vector(index, add), std::out_of_range)
      << "Should throw out_of_range if provided index is not valid!";

  l.clear();
  EXPECT_THROW(l.push_vector(index, add), std::length_error)
      << "Should throw length_error if list is empty!";
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

  ListNode<int> wrong(100);
  EXPECT_THROW(l.remove_node(&wrong), std::invalid_argument)
      << "Should throw invalid_argument if node was not found!";

  EXPECT_THROW(l.remove_node(nullptr), std::invalid_argument)
      << "Should throw invalid_argument if node is equal to nullptr.";

  l.clear();
  EXPECT_THROW(l.remove_node(node1), std::length_error)
      << "Should throw length_error if list is empty!";
}

TEST(LinkedListModify, RemoveBefore) {
  std::vector<int> vec{5, 4, 3, 2};
  LinkedList<int> l(vec);

  ListNode<int> *node = l.get_tail();
  l.remove_before(node);

  EXPECT_THROW(l.remove_before(l.get_head()), std::invalid_argument)
      << "Should throw invalid_argument if before node is null!";

  node = l.get_head()->next;
  l.remove_before(node);

  EXPECT_THROW(l.remove_before(nullptr), std::invalid_argument)
      << "Should throw invalid_argument if node is null!";

  std::vector<int> expected{4, 2};
  int index = 0;
  ListNode<int> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  l.clear();
  EXPECT_THROW(l.remove_before(node), std::length_error)
      << "Should throw length_error if list is empty!";
}

TEST(LinkedListModify, RemoveAfter) {
  std::vector<int> vec{1, 2, 3, 4, 5, 6, 7};
  LinkedList<int> l(vec.begin(), vec.end());

  ListNode<int> *node = l.get_head()->next->next->next;
  l.remove_after(node);

  node = l.get_tail()->prev;
  l.remove_after(node);

  EXPECT_THROW(l.remove_after(l.get_tail()), std::invalid_argument)
      << "Should throw invalid_argument if after node is null!";

  EXPECT_THROW(l.remove_after(nullptr), std::invalid_argument)
      << "Should throw invalid_argument if node is null!";

  std::vector<int> expected{1, 2, 3, 4, 6};
  int index = 0;
  ListNode<int> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  l.clear();
  EXPECT_THROW(l.remove_after(node), std::length_error)
      << "Should throw length_error if list is empty!";
}

TEST(LinkedListModify, RemoveValue) {
  std::vector<char> vec{'a', 'b', 'c', 'd'};
  LinkedList<char> l(vec);

  l.remove_value('b');

  EXPECT_THROW(l.remove_value('x'), std::invalid_argument)
      << "Should throw invalid_argument if node with provided value was not "
         "found!";

  std::vector<char> expected{'a', 'c', 'd'};
  int index = 0;
  ListNode<char> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  l.clear();
  EXPECT_THROW(l.remove_value('a'), std::length_error)
      << "Should throw length_error if list is empty!";
}

TEST(LinkedListModify, RemoveAll) {
  std::vector<double> vec{10.0, 20.0, 20.0, 10.0, 3.5,
                          4.2,  50.0, 20.0, 12.5, 20.0};
  LinkedList<double> l(vec);

  l.remove_all(20.0);

  EXPECT_THROW(l.remove_all(100.0), std::invalid_argument)
      << "Should throw invalid_argument if node was not found!";

  std::vector<double> expected{10.0, 10.0, 3.5, 4.2, 50.0, 12.5};
  int index = 0;
  ListNode<double> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  l.clear();
  EXPECT_THROW(l.remove_all(10.0), std::length_error)
      << "Should throw length_error if list is empty!";
}

TEST(LinkedListModify, RemoveIf) {
  std::vector<std::string> vec{"hello", "hi", "abc", "world", "123"};
  LinkedList<std::string> l(vec.begin(), vec.end());

  l.remove_if([](std::string str) { return str.size() <= 3; });
  l.remove_if([](std::string str) { return str.size() == 0; });

  std::vector<std::string> expected{"hello", "world"};
  int index = 0;
  ListNode<std::string> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, expected[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }

  l.clear();
  EXPECT_THROW(l.remove_if([](std::string str) { return str.size() == 0; }),
               std::length_error)
      << "Should throw length_error if list is empty!";
}

// ----------
// Iterators test
// ----------

TEST(LinkedListIterators, IteratorBegin) {
  std::vector<int> vec{5, 4, 3, 2, 1};
  LinkedList<int> l(vec);

  ListIterator<int> lit = l.begin();
  EXPECT_EQ(*lit, 5) << "Begin iterator should be at the first element!";
}

TEST(LinkedListIterators, IteratorEnd) {
  std::vector<int> vec{5, 4, 3, 2, 1};
  LinkedList<int> l(vec);

  ListIterator<int> lit = l.end();
  EXPECT_EQ(*lit, 1) << "End iterator should be pointing at the last element!";
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

TEST(LinkedListMethods, Contains) {
  std::vector<char> vec{'a', 'b', 'c', 'd', 'e'};
  LinkedList<char> l(vec.begin(), vec.end());

  ListNode<char> node('c');
  EXPECT_TRUE(l.contains(&node))
      << "Node with value 'c' should be in the list!";

  node = ListNode('d');
  EXPECT_TRUE(l.contains(&node))
      << "Node with value 'd' should be in the list!";

  node = ListNode('x');
  EXPECT_FALSE(l.contains(&node))
      << "Node with value 'd' should be in the list!";

  ListNode<char> *wrong = nullptr;
  EXPECT_THROW(l.contains(wrong), std::invalid_argument)
      << "Should throw invalid_argument if node is null!";

  l.clear();
  EXPECT_THROW(l.contains(wrong), std::length_error)
      << "Should throw length_error if list is empty!";
}

TEST(LinkedListMethods, ToVector) {
  std::vector<int> vec{1, 2, 3};
  LinkedList<int> l(vec.begin(), vec.end());

  std::vector<int> expected = l.to_vector();

  for (int i = 0; i < expected.size(); i++)
    EXPECT_EQ(expected[i], vec[i]) << "Values should be equal!";

  std::reverse(vec.begin(), vec.end());
  expected = l.to_vector(false);

  for (int i = 0; i < expected.size(); i++)
    EXPECT_EQ(expected[i], vec[i]) << "Values should be equal!";
}

TEST(LinkedListMethods, FromVector) {
  std::vector<bool> vec{true, false, false, true};
  LinkedList<bool> l = LinkedList<bool>::from_vector(vec);

  int index = 0;
  ListNode<bool> *temp = l.get_head();
  while (temp != nullptr) {
    EXPECT_EQ(temp->data, vec[index]) << "Values should be equal!";

    index++;
    temp = temp->next;
  }
}

TEST(LinkedListMethods, ToString) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  LinkedList<int> l(vec);

  std::string expected = "1 <-> 2 <-> 3 <-> 4 <-> 5";

  std::string result = l.to_string();
  EXPECT_EQ(result, expected) << "Strings should be equal!";

  expected = "5 <-> 4 <-> 3 <-> 2 <-> 1";
  result = l.to_string(false);
  EXPECT_EQ(result, expected) << "Strings should be equal!";

  l.clear();
  EXPECT_THROW(std::string e = l.to_string(), std::length_error)
      << "Should throw length_error if list is empty!";
}

TEST(LinkedListMethods, GetNode) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  LinkedList<int> l(vec);

  ListNode<int> *node = l.get_node_by_value(3);
  EXPECT_EQ(node, l.get_head()->next->next) << "Nodes should be equal!";

  EXPECT_THROW(l.get_node_by_value(100), std::invalid_argument)
      << "Should throw invalid_argument if node with provided value was not "
         "found!";

  node = l.get_node_by_index(4);
  EXPECT_EQ(node, l.get_tail()) << "Nodes should be equal!";

  EXPECT_THROW(l.get_node_by_index(-100), std::out_of_range)
      << "Should throw out_of_range if index is not valid!";

  l.clear();
  EXPECT_THROW(l.get_node_by_value(2), std::length_error)
      << "Should throw length_error if list is empty!";
  EXPECT_THROW(l.get_node_by_index(2), std::length_error)
      << "Should throw length_error if list is empty!";
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
  EXPECT_EQ(l.get_tail(), nullptr) << "Tail must be pointing to the nullptr!";
}
