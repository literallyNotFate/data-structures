#include <LinkedList.h>
#include <ListIterator.h>
#include <gtest/gtest.h>

#include <iostream>
#include <stdexcept>
#include <vector>

// ----------
// Constructor test
// ----------

TEST(ListIteratorConstructors, BasicConstructor) {
  std::vector<int> vec{1, 2, 3, 4, 5, 6};
  LinkedList<int> l(vec);

  ListIterator<int> lit(l);
  EXPECT_EQ(lit.get_node()->data, vec[0])
      << "Iterator should point to the first by default!";
}

// ----------
// Getter test
// ----------

TEST(ListIteratorGetters, GetNode) {
  std::vector<int> vec{1, 2, 3};
  LinkedList<int> l(vec);

  ListIterator<int> lit(l);
  EXPECT_NE(lit.get_node(), nullptr) << "Node should not be nullptr!";
}

// ----------
// Methods test
// ----------

TEST(ListIteratorMethods, IncrementOperator) {
  std::vector<std::string> vec{"a", "ab", "abc", "abcd", "abcde"};
  LinkedList<std::string> l(vec);

  ListIterator<std::string> lit(l);
  std::vector<std::string> expected{"a", "ab", "abc"};

  int n = 3, index = 0;
  while (n > 0) {
    EXPECT_EQ(*lit, expected[index]) << "Values should be equal!";

    index++;
    ++lit;
    n--;
  }
}

TEST(ListIteratorMethods, DecrementOperator) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  LinkedList<int> l(vec);

  ListIterator<int> lit(l.get_tail());
  std::vector<int> expected{5, 4, 3, 2, 1};

  int n = expected.size(), index = 0;
  while (n > 0) {
    EXPECT_EQ(*lit, expected[index]) << "Values should be equal!";

    index++;
    --lit;
    n--;
  }
}

TEST(ListIteratorMethods, DereferenceOperator) {
  std::vector<float> vec{1.0, 2.0, 3.0, 4.0};
  LinkedList<float> l(vec);

  ListIterator<float> lit(l);
  EXPECT_EQ(*lit, vec[0]) << "Iterator should be at 1st element";

  ++lit;
  EXPECT_EQ(*lit, vec[1]) << "Iterator should be at 2nd element";
}

TEST(ListIteratorMethods, ArrowOperator) {
  class Pet {
  public:
    std::string name;
    Pet(std::string n) : name(n) {};
  };

  std::vector<Pet> vec{Pet("Michael"), Pet("Alice"), Pet("Ringo")};
  LinkedList<Pet> l(vec);
  ListIterator<Pet> lit(l);

  std::string *names = new std::string[vec.size()]{"Michael", "Alice", "Ringo"};

  for (int i = 0; i < vec.size(); ++i, ++lit)
    EXPECT_EQ(lit->name, names[i]) << "Values should be equal!";
}

TEST(ListIteratorMethods, AdditionOperator) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  LinkedList<int> l(vec);

  ListIterator<int> lit(l);
  auto lit2 = lit + 2;

  EXPECT_EQ(*lit2, 3) << "Value should be equal to 3!";

  lit2 = lit2 + 10;
  EXPECT_EQ(*lit2, vec[vec.size() - 1])
      << "Iterator should be at the last element!";

  EXPECT_THROW(lit2 + (-2), std::invalid_argument)
      << "Should throw invalid_argument exception if value is < 0!";
}

TEST(ListIteratorMethods, SubstractionOperator) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  LinkedList<int> l(vec);

  ListIterator<int> lit(l.get_tail());
  auto lit2 = lit - 1;

  EXPECT_EQ(*lit2, 4) << "Value should be equal to 4!";

  lit2 = lit2 - 10;
  EXPECT_EQ(*lit2, vec[0]) << "Iterator should be at the first element!";

  EXPECT_THROW(lit2 - (-2), std::invalid_argument)
      << "Should throw invalid_argument exception if value is < 0!";
}

TEST(ListIteratorMethods, Advance) {
  std::vector<char> vec{'a', 'b', 'c', 'd', 'e'};
  LinkedList<char> l(vec.begin(), vec.end());

  ListIterator<char> lit(l);

  ListIterator<char>::advance(lit, 2);
  EXPECT_EQ(*lit, 'c') << "Value should be equal to 'c'!";

  ListIterator<char>::advance(lit, 100);
  EXPECT_EQ(*lit, vec[vec.size() - 1]) << "Value should be equal to 'e'!";

  ListIterator<char>::advance(lit, -3);
  EXPECT_EQ(*lit, vec[1]) << "Value should be equal to 'b'!";

  ListIterator<char>::advance(lit, -100);
  EXPECT_EQ(*lit, vec[0]) << "Value should be equal to 'a'!";
}

// ----------
// Compare test
// ----------

TEST(ListIteratorCompare, EqualityOperator) {
  std::vector<int> vec{1, 2, 3};
  LinkedList<int> l(vec.begin(), vec.end());

  ListIterator<int> lit1(l), lit2(l);

  EXPECT_TRUE(lit1 == lit2)
      << "LinkedList iterators lit1 and lit2 should be equal!";
}

TEST(ListIteratorCompare, InequalityOperator) {
  std::vector<int> vec{1, 2, 3};
  LinkedList<int> l1(vec), l2(vec.begin() + 1, vec.end());

  ListIterator<int> lit1(l1), lit2(l2);

  EXPECT_TRUE(lit1 != lit2)
      << "LinkedList iterators lit1 and lit2 should not be equal!";
}
