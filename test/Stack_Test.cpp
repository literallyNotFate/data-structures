#include <Iterator.h>
#include <Stack.h>
#include <gtest/gtest.h>

#include <iostream>
#include <stdexcept>
#include <vector>

// ----------
// Constructors test
// ----------

TEST(StackConstructor, CapacityConstructor) {
  int capacity = 10;
  Stack<int> s(capacity);

  EXPECT_EQ(s.get_size(), 0) << "Should be 0 sized!";
  EXPECT_EQ(s.get_capacity(), capacity)
      << "Must have specified capacity = " << capacity;
  EXPECT_NE(s.get_stack(), nullptr) << "Stack must be initialized!";
}

TEST(StackConstructor, FillConstructor) {
  std::string fill = "abc";
  int size = 5;
  Stack<std::string> s(5, fill);

  EXPECT_EQ(s.get_size(), size) << "Should be sized " << size;
  EXPECT_EQ(s.get_capacity(), size) << "Should have capacity: " << size;

  while (!s.is_empty()) {
    EXPECT_EQ(s.pop(), fill) << "Values should be equal!";
  }
}

TEST(StackConstructor, ArrayBasedConstructor) {
  int size = 5;
  int *int_array = new int[]{1, 2, 3, 4, 5};
  Stack<int> s(size, int_array);

  EXPECT_EQ(s.get_size(), size)
      << "Stack size should be based array size: " << size;
  EXPECT_EQ(s.get_capacity(), size)
      << "Stack capacity should be based array capacity: " << size;

  std::vector<int> expected{5, 4, 3, 2, 1};
  int i = 0;

  while (!s.is_empty()) {
    EXPECT_EQ(s.pop(), expected[i]) << "Values should be equal!";
    i++;
  }
}

TEST(StackConstructor, VectorBasedConstructor) {
  std::vector<int> vec{1, 2, 3};
  Stack<int> s(vec);

  EXPECT_EQ(s.get_size(), vec.size())
      << "Stack size should be based vector size: " << vec.size();
  EXPECT_EQ(s.get_capacity(), vec.size())
      << "Stack capacity should be based vector size: " << vec.size();

  std::vector<int> expected{3, 2, 1};
  int i = 0;

  while (!s.is_empty()) {
    EXPECT_EQ(s.pop(), expected[i]) << "Values should be equal!";
    i++;
  }
}

TEST(StackConstructor, RangeBasedConstructor) {
  std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Stack<int> s(vec.begin(), vec.end());

  EXPECT_EQ(s.get_size(), vec.size())
      << "Stack size should be based vector size: " << vec.size();
  EXPECT_EQ(s.get_capacity(), vec.size())
      << "Stack capacity should be based vector size: " << vec.size();

  std::vector<int> expected{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int i = 0;

  while (!s.is_empty()) {
    EXPECT_EQ(s.pop(), expected[i]) << "Values should be equal!";
    i++;
  }

  EXPECT_THROW(Stack<int> s1(vec.end(), vec.begin()), std::invalid_argument)
      << "Should throw invalid_argument if first iterator is greater than the "
         "second!";
}

TEST(StackConstructor, CopyConstructor) {
  Stack<int> s1(3, 0);
  Stack<int> s2(s1);

  EXPECT_EQ(s1.get_size(), s2.get_size())
      << "Sizes of copies should be equal !";
  EXPECT_EQ(s1.get_capacity(), s2.get_capacity())
      << "Capacities of copies should be eqial!";

  EXPECT_TRUE(s1 == s2) << "Values for dynamic arrays must be equal!";
}

TEST(StackConstructor, Destructor) {
  int size = 3;
  Stack<bool> s(size, false);

  EXPECT_EQ(s.get_size(), size) << "Size should be: " << size;
  EXPECT_EQ(s.get_capacity(), size) << "Capacity should be: " << size;

  while (!s.is_empty())
    EXPECT_EQ(s.pop(), false) << "Values should be equal!";

  s.~Stack<bool>();

  EXPECT_EQ(s.get_stack(), nullptr) << "Memory of array should be cleared!";
}

// ----------
// Operator tests
// ----------

TEST(StackOperators, GreaterThan) {
  int *int_array1 = new int[]{1, 2, 3};
  int *int_array2 = new int[]{4, 5, 6};
  Stack<int> s1(3, int_array1);
  Stack<int> s2(2, int_array1);
  Stack<int> s3(3, int_array2);

  EXPECT_TRUE(s1 > s2) << "s1 should be greater than s2 (" << s1.get_size()
                       << " > " << s2.get_size() << ").";

  EXPECT_FALSE(s1 > s1) << "Should return false because arrays are equal!";
  EXPECT_FALSE(s1 > s3)
      << "Should return true because ALL values of s3 > ALL values of s1.";
}

TEST(StackOperators, LessThan) {
  int *int_array1 = new int[]{1, 2, 3};
  int *int_array2 = new int[]{4, 5, 6};
  Stack<int> s1(3, int_array1);
  Stack<int> s2(2, int_array1);
  Stack<int> s3(3, int_array2);

  EXPECT_TRUE(s2 < s1) << "s2 should be less than s1 (" << s2.get_size()
                       << " < " << s1.get_size() << ").";

  EXPECT_FALSE(s1 < s1) << "Should return false because arrays are equal!";
  EXPECT_FALSE(s3 < s1)
      << "Should return true because ALL values of s1 < ALL values of s3.";
}

TEST(StackOperators, EqualityOperator) {
  Stack<int> s1(3, 0);
  Stack<int> s2(3, 0);
  Stack<int> s3(3, 1);

  EXPECT_TRUE(s1 == s2) << "s1 and s2 should be equal!";
  EXPECT_FALSE(s1 == s3) << "s1 and s3 should not be equal!";
}

TEST(StackOperators, InequalityOperator) {
  Stack<int> s1(3, 0);
  Stack<int> s2(3, 0);
  Stack<int> s3(3, 1);

  EXPECT_FALSE(s1 != s2) << "s1 and s2 should not be unequal!";
  EXPECT_TRUE(s1 != s3) << "s1 and s3 should be unequal!";
}

// ----------
// Modify stack tests
// ----------

TEST(StackModify, Push) {
  Stack<int> s(3);
  s.push(1);
  s.push(2);
  s.push(3);

  std::vector<int> expected{3, 2, 1};
  Stack<int> dummy(s);
  int i = 0;

  while (!dummy.is_empty()) {
    EXPECT_EQ(dummy.peek(), expected[i]) << "Values should be equal!";
    dummy.pop();
    i++;
  }

  EXPECT_THROW(s.push(4), std::overflow_error)
      << "Should throw overflow_error if stack is full!";
}

TEST(StackModify, Pop) {
  std::vector<int> vec{1, 2};
  Stack<int> s(vec);

  int pop = s.pop();
  EXPECT_EQ(pop, vec[vec.size() - 1]) << "Values should be equal!";

  pop = s.pop();
  EXPECT_EQ(pop, vec[0]) << "Values should be equal!";

  EXPECT_EQ(s.get_size(), 0) << "Stack should be empty after 2 pops!";

  EXPECT_THROW(s.pop(), std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}

TEST(StackModify, Insert) {
  Stack<int> s(6);

  s.push(1);
  s.push(2);
  s.push(3);

  int index = 1, value = 99;
  EXPECT_EQ(s[0], 1) << "1st element should equal 1.";

  s.insert(index, value);
  EXPECT_EQ(s[index], value)
      << "Element at index: " << index << " should be equal: " << value;

  index = 2, value = -99;
  s.insert(index, value);
  EXPECT_EQ(s[index], value)
      << "Element at index: " << index << " should be equal: " << value;

  index = 99;
  EXPECT_THROW(s.insert(index, value), std::out_of_range)
      << "Should throw out_of_range because index: " << index
      << " is out of range!";

  s.push(40);
  EXPECT_THROW(s.insert(index, value), std::overflow_error)
      << "Should throw overflow_error if stack is full!";
}

// ----------
// Iterators test
// ----------

TEST(StackIterators, IteratorBegin) {
  Stack<char> s(5);

  s.push('a');
  s.push('b');
  s.push('c');

  for (int i = 0; i < s.get_size(); i++) {
    std::cout << s[i] << " ";
  }

  std::cout << std::endl << std::endl;

  Iterator<char> it = s.begin();

  EXPECT_EQ(*it, 'a') << "First element should be equal to 'c'.";
  EXPECT_EQ(it.get_index(), 0) << "Index should be 0!";
}

TEST(StackIterators, IteratorEnd) {
  Stack<char> s(5);

  s.push('a');
  s.push('b');
  s.push('c');

  Iterator<char> it = s.end();

  EXPECT_EQ(*it, 'c') << "Last element should be equal to 'c'.";
  EXPECT_EQ(it.get_index(), s.get_top())
      << "Index should be " << s.get_top() << ".";
}

// ----------
// Methods test
// ----------

TEST(StackMethods, Resize) {
  int size = 1;
  Stack<std::string> s(size, "abc");
  std::string *old_stack = s.get_stack();

  EXPECT_EQ(s.get_size(), size) << "Size should be: " << size;
  EXPECT_EQ(s.get_capacity(), size) << "Capacity should be: " << size;
  EXPECT_NE(old_stack, nullptr);

  int new_capacity = 10;
  s.resize(new_capacity);
  std::string *new_stack = s.get_stack();

  EXPECT_EQ(s.get_size(), size) << "New size should be: " << size;
  EXPECT_EQ(s.get_capacity(), new_capacity)
      << "New capacity should be: " << new_capacity;
  EXPECT_NE(&old_stack, &new_stack)
      << "New array must point to another address as the old one!";

  new_capacity = 3;
  s.resize(new_capacity);
  EXPECT_NE(s.get_capacity(), new_capacity)
      << "Capacity should not be changed!";
}

TEST(StackMethods, EqualOperation) {
  int size1 = 3;
  int size2 = 5;
  Stack<int> s1(size1, 1);
  Stack<int> s2(size2, 0);

  EXPECT_EQ(s1.get_size(), size1)
      << "Old Size of the first before should be: " << size1;
  EXPECT_NE(s1.get_stack(), s2.get_stack()) << "Arrays should not be equal!";

  for (int i = 0; i < size1; i++)
    EXPECT_EQ(s1[i], 1)
        << "Should be equal to specified fill value from array 1!";

  s1 = s2;

  EXPECT_EQ(s1.get_size(), size2)
      << "New Size of the first after should be: " << size2;

  for (int i = 0; i < size2; i++)
    EXPECT_EQ(s1[i], 0)
        << "Should be equal to specified fill value from array 2!";
}

TEST(StackMethods, Peek) {
  std::vector<char> vec{'a', 'b', 'c'};
  Stack<char> s(vec);

  std::vector<char> expected{'c', 'b', 'a'};
  int i = 0;

  while (!s.is_empty()) {
    EXPECT_EQ(s.peek(), expected[i]);
    s.pop();
    i++;
  }

  EXPECT_THROW(s.peek(), std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}

TEST(StackMethods, Bottom) {
  std::vector<char> vec{'a', 'b', 'c'};
  Stack<char> s(vec);

  EXPECT_EQ(s.bottom(), 'a') << "Bottom element should be equal to 'a'.";

  while (!s.is_empty())
    s.pop();

  EXPECT_THROW(s.bottom(), std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}

TEST(StackMethods, At) {
  std::vector<std::string> vec{"abc", "123", "hello"};
  int index = 99;
  Stack<std::string> s(vec.begin() + 1, vec.end());

  EXPECT_EQ(s.at(0), vec[1]) << "Should return element at 0 index!";
  EXPECT_THROW(s[index], std::out_of_range)
      << "Should throw out_of_range if index is wrong. Index: " << index;

  while (!s.is_empty())
    s.pop();

  EXPECT_THROW(s[0], std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}
