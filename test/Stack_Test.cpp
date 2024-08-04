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
// Compare tests
// ----------

TEST(StackCompare, GreaterThan) {
  int *int_array1 = new int[]{1, 2, 3}, *int_array2 = new int[]{4, 5, 6};
  Stack<int> s1(3, int_array1), s2(2, int_array1), s3(3, int_array2);

  EXPECT_TRUE(s1 > s2) << "s1 should be greater than s2 (" << s1.get_size()
                       << " > " << s2.get_size() << ").";

  EXPECT_FALSE(s1 > s1) << "Should return false because arrays are equal!";
  EXPECT_FALSE(s1 > s3)
      << "Should return true because ALL values of s3 > ALL values of s1.";
}

TEST(StackCompare, LessThan) {
  int *int_array1 = new int[]{1, 2, 3}, *int_array2 = new int[]{4, 5, 6};
  Stack<int> s1(3, int_array1), s2(2, int_array1), s3(3, int_array2);

  EXPECT_TRUE(s2 < s1) << "s2 should be less than s1 (" << s2.get_size()
                       << " < " << s1.get_size() << ").";

  EXPECT_FALSE(s1 < s1) << "Should return false because arrays are equal!";
  EXPECT_FALSE(s3 < s1)
      << "Should return true because ALL values of s1 < ALL values of s3.";
}

TEST(StackCompare, EqualityOperator) {
  Stack<int> s1(3, 0), s2(3, 0), s3(3, 1);

  EXPECT_TRUE(s1 == s2) << "s1 and s2 should be equal!";
  EXPECT_FALSE(s1 == s3) << "s1 and s3 should not be equal!";
}

TEST(StackCompare, InequalityOperator) {
  Stack<int> s1(3, 0), s2(3, 0), s3(3, 1);

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

TEST(StackModify, Erase) {
  Stack<int> s(10);
  int size = 3;

  s.push(1);
  s.push(2);
  s.push(3);

  Iterator<int> it(s.get_stack(), s.get_size());
  s.erase(it + 1);
  --size;

  EXPECT_EQ(s.get_size(), size) << "Size should be 2 after deletion!";

  EXPECT_THROW(s.erase(it + 99), std::out_of_range)
      << "Should throw out_of_range!";
  EXPECT_THROW(s.erase(it - 99), std::out_of_range)
      << "Should throw out_of_range!";

  s.erase_range(s.begin(), s.end());
  EXPECT_THROW(s.erase(s.begin()), std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}

TEST(StackModify, EraseRange) {
  Stack<int> s(10);
  int size = 5, range = 3;

  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);
  s.push(5);

  Iterator<int> it(s.get_stack(), s.get_size());

  EXPECT_THROW(s.erase_range(it - 99, it + 1), std::out_of_range)
      << "Should throw out_of_range!";
  EXPECT_THROW(s.erase_range(it + 1, it + 99), std::out_of_range)
      << "Should throw out_of_range!";
  EXPECT_THROW(s.erase_range(it + 2, it + 1), std::invalid_argument)
      << "it1 should be less than it2!";

  s.erase_range(it + 1, it + 3);
  size -= range;

  EXPECT_EQ(s.get_size(), size)
      << "Size should be " << size << " after range deletion!";
}

// ----------
// Iterators test
// ----------

TEST(StackIterators, IteratorBegin) {
  Stack<char> s(5);

  s.push('a');
  s.push('b');
  s.push('c');

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
  int size1 = 3, size2 = 5;
  Stack<int> s1(size1, 1), s2(size2, 0);

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

TEST(StackMethods, ToVector) {
  Stack<char> s(10);

  s.push('a');
  s.push('b');
  s.push('c');

  std::vector<char> svec = s.to_vector();
  for (int i = 0; i < s.get_size(); i++)
    EXPECT_EQ(s[i], svec[i])
        << "Elements of stack and vector should be equal to each other!";
}

TEST(StackMethods, FromVector) {
  std::vector<char> vec;

  vec.push_back('a');
  vec.push_back('b');
  vec.push_back('c');

  Stack<char> s = Stack<char>::from_vector(vec);
  EXPECT_EQ(vec.size(), s.get_size())
      << "Vector and stack sizes should be equal!";

  for (int i = 0; i < s.get_size(); i++)
    EXPECT_EQ(s[i], vec[i])
        << "Elements of stack and vector should be equal to each other!";
}

TEST(StackMethods, ToString) {
  Stack<char> s(10);

  s.push('a');
  s.push('b');
  s.push('c');

  std::string str = s.to_string();
  std::string res = "c\n---\nb\n---\na\n";

  EXPECT_EQ(str, res) << "Strings should be equal to each other!";

  s.erase_range(s.begin(), s.end());
  EXPECT_THROW(str = s.to_string(), std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}

TEST(StackMethods, Contains) {
  std::vector<std::string> vec{"abc", "hello", "world"};
  Stack<std::string> s(vec);

  std::string el = "abc";
  EXPECT_TRUE(s.contains(el)) << "String should be in the stack!";

  el = "123";
  EXPECT_FALSE(s.contains(el)) << "String should not be in the stack!";
}

TEST(StackMethods, Find) {
  std::vector<int> vec{1, 3, 5, 7, 9, 11};
  Stack<int> s(vec);

  int el = 1;
  Iterator<int> it = s.find(el);

  EXPECT_EQ(*it, 1) << "Should be equal to found element!";
  EXPECT_EQ(it.get_index(), s.begin().get_index())
      << "Iterator should point to the first element!";

  el = 11;
  it = s.find(el);

  EXPECT_EQ(*(it - 1), 9) << "Should point to the previous element (9).";

  el = 100;
  it = s.find(el);

  EXPECT_EQ(it.get_index(), s.end().get_index())
      << "Should point to the end if not found!";

  s.erase_range(s.begin(), s.end());
  EXPECT_THROW(it = s.find(el), std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}

TEST(StackMethods, FindAll) {
  std::vector<int> vec{1, 2, 1, 3, 1, 4, 1};
  Stack<int> s(vec);

  int el = 1;
  Iterator<int> it = s.begin();
  std::vector<Iterator<int>> iterators = s.find_all(el);

  std::vector<Iterator<int>> expected{it, it + 2, it + 4, it + 6};

  for (int i = 0; i < iterators.size(); i++)
    EXPECT_EQ(iterators[i], expected[i])
        << "Expected iterators and result iterators should be equal!";

  el = 99;
  iterators = s.find_all(el);

  EXPECT_EQ(iterators.size(), 0)
      << "Vector size should be 0 if nothing was found!";

  s.erase_range(s.begin(), s.end());
  EXPECT_THROW(s.find_all(el), std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}

TEST(StackMethods, FindIf) {
  std::vector<std::string> vec{"123", "hi", "hello", "world"};
  Stack<std::string> s(vec);

  std::vector<Iterator<std::string>> iterators =
      s.find_if([](std::string str) { return str.size() > 3; });
  std::vector<Iterator<std::string>> expected{s.end() - 1, s.end()};

  for (int i = 0; i < iterators.size(); i++)
    EXPECT_EQ(iterators[i].get_index(), expected[i].get_index())
        << "Expected iterators and result iterators should be equal!";

  iterators = s.find_if([](std::string str) { return str.size() < 2; });
  EXPECT_EQ(iterators.size(), 0)
      << "Vector size should be 0 if nothing was found!";

  s.erase_range(s.begin(), s.end());
  EXPECT_THROW(s.find_if([](std::string str) { return str.size() < 2; }),
               std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}

TEST(StackMethods, Replace) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  Stack<int> s(vec);

  int el = 3;
  s.replace(el, 99);
  std::vector<int> expected{1, 2, 99, 4, 5};

  for (int i = 0; i < expected.size(); i++)
    EXPECT_EQ(s[i], expected[i])
        << "Values of expected and result stack should be equal!";

  el = 100;
  EXPECT_THROW(s.replace(el, 50), std::invalid_argument)
      << "Should throw invalid_argument if element was not found!";

  s.erase_range(s.begin(), s.end());
  EXPECT_THROW(s.replace(el, 50), std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}

TEST(StackMethods, ReplaceAll) {
  std::vector<char> vec{'a', 'b', 'b', 'c', 'd', 'b'};
  Stack<char> s(vec);

  char el = 'b';
  s.replace_all(el, 'x');
  std::vector<char> expected{'a', 'x', 'x', 'c', 'd', 'x'};

  for (int i = 0; i < expected.size(); i++)
    EXPECT_EQ(s[i], expected[i])
        << "Values of expected and result stack should be equal!";

  el = 'h';
  EXPECT_THROW(s.replace_all(el, 'n'), std::invalid_argument)
      << "Should throw invalid_argument if element was not found!";

  s.erase_range(s.begin(), s.end());
  EXPECT_THROW(s.replace_all(el, 'n'), std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}

// ----------
// Useful functions test
// ----------

TEST(StackUsefulFunctions, TopN) {
  std::vector<int> vec{1, 2, 3, 4, 5, 6};
  Stack<int> s(vec);

  int top = 3;
  std::vector<int> top_n = s.top_n(top);
  std::vector<int> expected = {6, 5, 4};

  for (int i = 0; i < top_n.size(); i++)
    EXPECT_EQ(top_n[i], expected[i])
        << "Values of the top and expected should be equal!";

  top = -2;
  EXPECT_THROW(s.top_n(top), std::invalid_argument)
      << "Should throw invalid_argument if n < 0!";

  top = 99;
  EXPECT_THROW(s.top_n(top), std::invalid_argument)
      << "Should throw invalid_argument if n > size of the stack!";

  s.erase_range(s.begin(), s.end());
  EXPECT_THROW(s.top_n(top), std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}

TEST(StackUsefulFunctions, BottomN) {
  std::vector<int> vec{1, 2, 3, 4, 5, 6};
  Stack<int> s(vec);

  int bottom = 3;
  std::vector<int> bottom_n = s.bottom_n(bottom);
  std::vector<int> expected = {1, 2, 3};

  for (int i = 0; i < bottom_n.size(); i++)
    EXPECT_EQ(bottom_n[i], expected[i])
        << "Values of the bottom and expected should be equal!";

  bottom = -2;
  EXPECT_THROW(s.bottom_n(bottom), std::invalid_argument)
      << "Should throw invalid_argument if n < 0!";

  bottom = 99;
  EXPECT_THROW(s.bottom_n(bottom), std::invalid_argument)
      << "Should throw invalid_argument if n > size of the stack!";

  s.erase_range(s.begin(), s.end());
  EXPECT_THROW(s.bottom_n(bottom), std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}

TEST(StackUsefulFunctions, Count) {
  std::vector<char> vec{'a', 'b', 'c', 'd', 'd'};
  Stack<char> s(vec);

  int count = s.count('d');
  EXPECT_EQ(count, 2) << "'d' should encounter 2 times!";

  count = s.count('x');
  EXPECT_EQ(count, 0) << "Should return 0 if nothing was found!";
}

TEST(StackUsefulFunctions, CountIf) {
  std::vector<float> vec{10.0, 2.5, 6.3, 6.1, 12.6, 4.6, 50.1, 20.3, 11.4, 8.2};
  Stack<float> s(vec);

  int count = s.count_if([](float x) { return x > 10.0; });
  EXPECT_EQ(count, 4) << "Elements that are > 10.0 should be 4!";

  count = s.count_if([](float x) { return x < 0.0; });
  EXPECT_EQ(count, 0) << "Should return 0 if nothing was found!";
}

TEST(StackMinMax, Min) {
  std::vector<int> vec1{1, 2, 3, 4, 5, 10, 6, 7};
  Stack<int> s1(vec1);

  int min1 = s1.min();
  EXPECT_EQ(min1, 1) << "Min element in the stack should be equal to 1!";

  s1.erase_range(s1.begin(), s1.end());
  EXPECT_THROW(s1.min(), std::underflow_error)
      << "Should throw underflow_error if stack is empty!";

  std::vector<std::string> vec2{"abc", "def", "hello", "hi", "yo", "world"};
  Stack<std::string> s2(vec2);

  std::string min2 = s2.min([](std::string str) { return str.size(); });
  EXPECT_EQ(min2, "hi") << "'hi' must be the string with min length!";

  s2.erase_range(s2.begin(), s2.end());
  EXPECT_THROW(s2.min([](std::string str) { return str.size(); }),
               std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}

TEST(StackMinMax, Max) {
  std::vector<int> vec1{1, 2, 3, 4, 5, 10, 6, 7};
  Stack<int> s1(vec1);

  int max1 = s1.max();
  EXPECT_EQ(max1, 10) << "Max element in the stack should be equal to 10!";

  s1.erase_range(s1.begin(), s1.end());
  EXPECT_THROW(s1.max(), std::underflow_error)
      << "Should throw underflow_error if stack is empty!";

  std::vector<std::string> vec2{"abc", "def", "hello", "hi", "yo", "world"};
  Stack<std::string> s2(vec2);

  std::string max2 = s2.max([](std::string str) { return str.size(); });
  EXPECT_EQ(max2, "hello") << "'hello' must be the string with max length!";

  s2.erase_range(s2.begin(), s2.end());
  EXPECT_THROW(s2.max([](std::string str) { return str.size(); }),
               std::underflow_error)
      << "Should throw underflow_error if stack is empty!";
}
