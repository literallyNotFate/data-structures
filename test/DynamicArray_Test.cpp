#include <DynamicArray.h>
#include <Iterator.h>

#include <gtest/gtest.h>

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <sys/errno.h>
#include <vector>

// ----------
// Constructors test
// ----------

TEST(DynamicArrayConstructors, CapacityConstructor) {
  int capacity = 10;
  DynamicArray<int> d(capacity);

  EXPECT_EQ(d.get_size(), 0) << "Should be 0 sized!";
  EXPECT_EQ(d.get_capacity(), capacity)
      << "Must have specified capacity = " << capacity;
  EXPECT_NE(d.get_array(), nullptr) << "Array must be initialized!";
}

TEST(DynamicArrayConstructors, FillConstructor) {
  std::string fill = "abc";
  int size = 5;
  DynamicArray<std::string> d(5, fill);

  EXPECT_EQ(d.get_size(), size) << "Should be sized " << size;
  EXPECT_EQ(d.get_capacity(), size) << "Should have capacity: " << size;

  for (int i = 0; i < d.get_size(); i++)
    EXPECT_EQ(d[i], fill) << "Should equal to fill value = " << fill;
}

TEST(DynamicArrayConstructors, ArrayBasedConstructor) {
  int size = 5;
  int *int_array = new int[]{1, 2, 3, 4, 5};
  DynamicArray<int> d(size, int_array);

  EXPECT_EQ(d.get_size(), size)
      << "Dynamic array size should be based array size: " << size;
  EXPECT_EQ(d.get_capacity(), size)
      << "Dynamic array capacity should be based array capacity: " << size;

  for (int i = 0; i < size; i++)
    EXPECT_EQ(int_array[i], d[i]) << "Should be equal to each other ("
                                  << int_array[i] << " = " << d[i] << ").";
}

TEST(DynamicArrayConstructors, VectorBasedConstructor) {
  std::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  DynamicArray<int> d(vec);

  EXPECT_EQ(d.get_size(), vec.size())
      << "Dynamic array size should be based vector size: " << vec.size();
  EXPECT_EQ(d.get_capacity(), vec.size())
      << "Dynamic array capacity should be based vector size: " << vec.size();

  for (int i = 0; i < vec.size(); i++)
    EXPECT_EQ(d[i], vec[i])
        << "Should be equal to each other (" << d[i] << " = " << vec[i] << ").";
}

TEST(DynamicArrayConstructor, CopyConstructor) {
  DynamicArray<int> d1(3, 0);
  DynamicArray<int> d2(d1);

  EXPECT_EQ(d1.get_size(), d2.get_size())
      << "Sizes of copies should be equal !";
  EXPECT_EQ(d1.get_capacity(), d2.get_capacity())
      << "Capacities of copies should be eqial!";

  EXPECT_TRUE(d1 == d2) << "Values for dynamic arrays must be equal!";
}

TEST(DynamicArrayConstructor, RandomRangeConstructor) {
  int size = 5;
  int min = 1;
  int max = 10;
  DynamicArray<int> d(size, min, max);

  EXPECT_EQ(d.get_size(), size) << "Size should be: " << size;
  EXPECT_EQ(d.get_capacity(), size) << "Capacity should be: " << size;

  for (int i = 0; i < size; ++i) {
    EXPECT_GE(d[i], min) << "Should be more than lower limit = " << min;
    EXPECT_LE(d[i], max) << "Should be less than higher linmit = " << max;
  }
}

TEST(DynamicArrayConstructor, StringBasedConstructor) {
  std::string s = "hello";
  DynamicArray<char> d(s);

  EXPECT_EQ(d.get_size(), s.size())
      << "Size should be the size of the string = " << s.size();
  EXPECT_EQ(d.get_capacity(), s.size())
      << "Capacity should be the size of the string = " << s.size();

  for (int i = 0; i < s.size(); i++)
    EXPECT_EQ(d[i], s[i]) << "Elemebnt of array should be equal to "
                             "corresponding character in string!";
}

TEST(DynamicArrayConstuctor, Destructor) {
  int size = 3;
  DynamicArray<bool> d(size, false);

  EXPECT_EQ(d.get_size(), size) << "Size should be: " << size;
  EXPECT_EQ(d.get_capacity(), size) << "Capacity should be: " << size;

  for (int i = 0; i < size; i++)
    EXPECT_NE(d[i], true);

  d.~DynamicArray<bool>();

  EXPECT_EQ(d.get_array(), nullptr) << "Memory of array should be cleared!";
}

// ----------
// Operator tests
// ----------

TEST(DynamicArrayOperators, GreaterThan) {
  int *int_array1 = new int[]{1, 2, 3};
  int *int_array2 = new int[]{4, 5, 6};
  DynamicArray<int> d1(3, int_array1);
  DynamicArray<int> d2(2, int_array1);
  DynamicArray<int> d3(3, int_array2);

  EXPECT_TRUE(d1 > d2) << "d1 should be greater than d2 (" << d1.get_size()
                       << " > " << d2.get_size() << ").";

  EXPECT_FALSE(d1 > d1) << "Should return false because arrays are equal!";
  EXPECT_FALSE(d1 > d3)
      << "Should return true because ALL values of d3 > ALL values of d1.";
}

TEST(DynamicArrayOperators, LessThan) {
  int *int_array1 = new int[]{1, 2, 3};
  int *int_array2 = new int[]{4, 5, 6};
  DynamicArray<int> d1(3, int_array1);
  DynamicArray<int> d2(2, int_array1);
  DynamicArray<int> d3(3, int_array2);

  EXPECT_TRUE(d2 < d1) << "d2 should be less than d1 (" << d2.get_size()
                       << " < " << d1.get_size() << ").";

  EXPECT_FALSE(d1 < d1) << "Should return false because arrays are equal!";
  EXPECT_FALSE(d3 < d1)
      << "Should return true because ALL values of d1 < ALL values of d3.";
}

TEST(DynamicArrayOperators, EqualityOperator) {
  DynamicArray<int> d1(3, 0);
  DynamicArray<int> d2(3, 0);
  DynamicArray<int> d3(3, 1);

  EXPECT_TRUE(d1 == d2) << "d1 and d2 should be equal!";
  EXPECT_FALSE(d1 == d3) << "d1 and d3 should not be equal!";
}

TEST(DynamicArrayOperators, InequalityOperator) {
  DynamicArray<int> d1(3, 0);
  DynamicArray<int> d2(3, 0);
  DynamicArray<int> d3(3, 1);

  EXPECT_FALSE(d1 != d2) << "d1 and d2 should not be unequal!";
  EXPECT_TRUE(d1 != d3) << "d1 and d3 should be unequal!";
}

// ----------
// Modify array tests
// ----------

TEST(DynamicArrayModify, PushBack) {
  char ch1 = 'a', ch2 = 'b', ch3 = 'c', ch4 = 'd';
  DynamicArray<char> d(3);

  d.push_back(ch1);
  EXPECT_EQ(d[0], ch1) << "1st element should equal: " << ch1;

  d.push_back(ch2);
  EXPECT_EQ(d[1], ch2) << "2nd element should equal: " << ch2;

  d.push_back(ch3);
  EXPECT_EQ(d[2], ch3) << "3rd element should equal: " << ch3;

  EXPECT_TRUE(d.is_full()) << "Array should be full!";
  EXPECT_THROW(d.push_back(ch4), std::length_error)
      << "Should throw length_error because array is full!";

  int new_capacity = 5;
  d.resize(new_capacity);
  EXPECT_EQ(d.get_capacity(), new_capacity)
      << "Array must be resized, new capacity = " << new_capacity;

  d.push_back(ch4);
  EXPECT_EQ(d[3], ch4) << "4th element (" << ch4
                       << ") must be added after resizing!";
}

TEST(DynamicArrayModify, PushBegin) {
  char ch1 = 'a', ch2 = 'b', ch3 = 'c', ch4 = 'd';
  DynamicArray<char> d(3);

  d.push_begin(ch1);
  EXPECT_EQ(d[0], ch1) << "1st element should equal: " << ch1;

  d.push_begin(ch2);
  EXPECT_EQ(d[0], ch2) << "New 1st element should equal: " << ch2;

  d.push_begin(ch3);
  EXPECT_EQ(d[0], ch3) << "New 1st element should equal: " << ch3;
  EXPECT_EQ(d[2], ch1) << ch1 << " should be shifted at the end!";

  EXPECT_TRUE(d.is_full()) << "Array should be full!";
  EXPECT_THROW(d.push_begin(ch4), std::length_error)
      << "Should throw length_error because array is full!";

  int new_capacity = 5;
  d.resize(new_capacity);
  EXPECT_EQ(d.get_capacity(), new_capacity)
      << "Array must be resized, new capacity = " << new_capacity;

  d.push_begin(ch4);
  EXPECT_EQ(d[1], ch3)
      << "2nd element should be the 1st element before resizing: " << ch3;
}

TEST(DynamicArrayModify, Insert) {
  DynamicArray<int> d(10);

  d.push_begin(3);
  d.push_begin(2);
  d.push_begin(1);

  int index = 1, value = 99;
  EXPECT_EQ(d[0], 1) << "1st element should equal 1.";

  d.insert(index, value);
  EXPECT_EQ(d[index], value)
      << "Element at index: " << index << " should be equal: " << value;

  index = 2, value = -99;
  d.insert(index, value);
  EXPECT_EQ(d[index], value)
      << "Element at index: " << index << " should be equal: " << value;

  index = 99;
  EXPECT_THROW(d.insert(index, value), std::out_of_range)
      << "Should throw out_of_range because index: " << index
      << " is out of range!";
}

TEST(DynamicArrayModify, InsertVector) {
  int capacity = 3;
  DynamicArray<int> d(capacity);

  d.push_back(1);
  d.push_back(2);

  EXPECT_EQ(d.get_capacity(), capacity)
      << "Capacity should be equal to " << capacity;

  std::vector<int> vec{10, 20, 30};
  int new_size = d.get_size() + vec.size();
  d.insert(1, vec);

  EXPECT_EQ(d.get_size(), new_size) << "Size should change to " << new_size;
  EXPECT_EQ(d.get_capacity(), new_size)
      << "Array should be resized to capacity: " << new_size;

  std::vector<int> expected{1, 10, 20, 30, 2};
  for (int i = 0; i < d.get_size(); i++)
    EXPECT_EQ(d[i], expected[i]) << "Values should be equal!";
}

TEST(DynamicArrayModify, EraseBack) {
  DynamicArray<int> d(5);
  int size = 2;

  d.push_back(1);
  d.push_back(2);

  d.erase_back();
  --size;

  EXPECT_EQ(d.get_size(), size)
      << "Size should be 1 after deletion of the last element!";
  EXPECT_FALSE(d.contains(2)) << "Deleted element should not be in the array!";

  d.erase_back();

  EXPECT_TRUE(d.is_empty()) << "Array must be empty after deleting everything!";
  EXPECT_THROW(d.erase_back(), std::length_error)
      << "Should throw length_error, because there are no elements to delete!";
}

TEST(DynamicArrayModify, EraseBegin) {
  DynamicArray<int> d(5);
  int size = 2;

  d.push_back(1);
  d.push_back(2);

  d.erase_begin();
  --size;

  EXPECT_EQ(d.get_size(), size)
      << "Size should be 1 after deletion of the last element!";
  EXPECT_FALSE(d.contains(1)) << "Deleted element should not be in the array!";

  d.erase_begin();

  EXPECT_TRUE(d.is_empty()) << "Array must be empty after deleting everything!";
  EXPECT_THROW(d.erase_back(), std::length_error)
      << "Should throw length_error, because there are no elements to delete!";
}

TEST(DynamicArrayModify, Erase) {
  DynamicArray<int> d(10);
  int size = 5;

  d.push_back(1);
  d.push_back(2);
  d.push_back(3);
  d.push_back(4);
  d.push_back(5);

  Iterator<int> it(d.get_array(), d.get_size());
  d.erase(it + 2);
  --size;

  EXPECT_EQ(d.get_size(), size) << "Size should be 4 after deletion!";
  EXPECT_FALSE(d.contains(3))
      << "Deleted element (" << *it << ") should not be in array!";

  EXPECT_THROW(d.erase(it + 99), std::out_of_range)
      << "Should throw out_of_range!";
  EXPECT_THROW(d.erase(it - 99), std::out_of_range)
      << "Should throw out_of_range!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d.erase(d.begin()), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayModify, EraseRange) {
  DynamicArray<int> d(10);
  int size = 5;
  int range = 3;

  d.push_back(1);
  d.push_back(2);
  d.push_back(3);
  d.push_back(4);
  d.push_back(5);

  Iterator<int> it(d.get_array(), d.get_size());

  EXPECT_THROW(d.erase_range(it - 99, it + 1), std::out_of_range)
      << "Should throw out_of_range!";
  EXPECT_THROW(d.erase_range(it + 1, it + 99), std::out_of_range)
      << "Should throw out_of_range!";
  EXPECT_THROW(d.erase_range(it + 2, it + 1), std::invalid_argument)
      << "it1 should be less than it2!";

  d.erase_range(it + 1, it + 3);
  size -= range;

  EXPECT_EQ(d.get_size(), size)
      << "Size should be " << size << " after range deletion!";

  EXPECT_TRUE(d.contains(*(d.begin())))
      << "First element should be in array: " << *(d.begin());
  EXPECT_TRUE(d.contains(*(d.end())))
      << "First element should be in array: " << *(d.end());

  EXPECT_FALSE(d.contains(2)) << "Deleted element (2) should not be in array!";
  EXPECT_FALSE(d.contains(3)) << "Deleted element (3) should not be in array!";
  EXPECT_FALSE(d.contains(4)) << "Deleted element (4) should not be in array!";
}

TEST(DynamicArrayModify, EraseAll) {
  int size = 5;
  int *int_array = new int[size]{1, 1, 2, 3, 1};
  DynamicArray<int> d(size, int_array);

  d.erase_all(1);

  size = 2;
  int *new_array = new int[size]{2, 3};

  for (int i = 0; i < size; i++)
    EXPECT_EQ(d[i], new_array[i]) << "Values of arrays should be equal!";

  // todo
}

TEST(DynamicArrayModify, EraseIf) {
  int size = 7;
  int *int_array = new int[size]{3, 4, 5, 2, 0, 5, 5};
  DynamicArray<int> d(size, int_array);

  d.erase_if([](int x) { return x % 2 != 0; });

  size = 3;
  int *new_array = new int[size]{4, 2, 0};

  EXPECT_EQ(d.get_size(), size) << "New size after erasing should be: " << size;
  for (int i = 0; i < size; i++)
    EXPECT_EQ(d[i], new_array[i]) << "Values of arrays should be equal!";

  d.erase_if([](int x) { return x > 10; });
  EXPECT_EQ(d.get_size(), size)
      << "Size should not change if elements were not found!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d.erase_if([](int x) { return x > 0; }), std::length_error)
      << "Should throw length_error if array is empty!";
}

// ----------
// Iterators test
// ----------

TEST(DynamicArrayIterators, IteratorBegin) {
  DynamicArray<char> d(5);

  d.push_back('a');
  d.push_back('b');
  d.push_back('c');

  Iterator<char> it = d.begin();

  EXPECT_EQ(*it, 'a') << "First element should be equal to 'a'.";
  EXPECT_EQ(it.get_index(), 0) << "Index should be 0!";
}

TEST(DynamicArrayIterators, IteratorEnd) {
  DynamicArray<char> d(5);

  d.push_back('a');
  d.push_back('b');
  d.push_back('c');

  Iterator<char> it = d.end();

  EXPECT_EQ(*it, 'c') << "Last element should be equal to 'c'.";
  EXPECT_EQ(it.get_index(), d.get_size() - 1)
      << "Index should be " << d.get_size() - 1 << ".";
}

// ----------
// Methods test
// ----------

TEST(DynamicArrayMethods, Resize) {
  int size = 1;
  DynamicArray<std::string> d(size, "abc");
  std::string *old_array = d.get_array();

  EXPECT_EQ(d.get_size(), size) << "Size should be: " << size;
  EXPECT_EQ(d.get_capacity(), size) << "Capacity should be: " << size;
  EXPECT_NE(old_array, nullptr);

  int new_capacity = 10;
  d.resize(new_capacity);
  std::string *new_array = d.get_array();

  EXPECT_EQ(d.get_size(), size) << "New size should be: " << size;
  EXPECT_EQ(d.get_capacity(), new_capacity)
      << "New capacity should be: " << new_capacity;
  EXPECT_NE(&old_array, &new_array)
      << "New array must point to another address as the old one!";

  new_capacity = 3;
  d.resize(new_capacity);
  EXPECT_NE(d.get_capacity(), new_capacity)
      << "Capacity should not be changed!";
}

TEST(DynamicArrayMethods, EqualOperation) {
  int size1 = 3;
  int size2 = 5;
  DynamicArray<int> d1(size1, 1);
  DynamicArray<int> d2(size2, 0);

  EXPECT_EQ(d1.get_size(), size1)
      << "Old Size of the first before should be: " << size1;
  EXPECT_NE(d1.get_array(), d2.get_array()) << "Arrays should not be equal!";

  for (int i = 0; i < size1; i++)
    EXPECT_EQ(d1[i], 1)
        << "Should be equal to specified fill value from array 1!";

  d1 = d2;

  EXPECT_EQ(d1.get_size(), size2)
      << "New Size of the first after should be: " << size2;

  for (int i = 0; i < size2; i++)
    EXPECT_EQ(d1[i], 0)
        << "Should be equal to specified fill value from array 2!";
}

TEST(DynamicArrayMethods, Contains) {
  std::string s1 = "abc";
  std::string s2 = "abs";
  DynamicArray<std::string> d(5, s1);

  EXPECT_FALSE(d.is_empty()) << "This array must not be empty!";

  EXPECT_TRUE(d.contains(s1)) << "Specified string must be in array: " << s1;
  EXPECT_FALSE(d.contains(s2))
      << "Specified string must not be in array: " << s2;
}

TEST(DynamicArrayMethods, At) {
  int *int_array = new int[]{1, 2, 3};
  int index = 99;
  DynamicArray<int> d(3, int_array);

  EXPECT_EQ(d.at(0), d[0]) << "Should return element at 0 index!";
  EXPECT_THROW(d[index], std::out_of_range)
      << "Should throw out_of_range if index is wrong. Index: " << index;
}

TEST(DynamicArrayMethods, Find) {
  int *int_array = new int[]{1, 2, 3, 4, 5};
  DynamicArray<int> d(5, int_array);

  Iterator<int> f = d.find(1);
  EXPECT_EQ(*f, *(d.begin())) << "Iterator should point at index 0!";
  EXPECT_EQ((d.find(5) - 1).get_index(), 3)
      << "Should point to the previous index of the found element at the end.";
  EXPECT_EQ(d.find(99), d.end())
      << "Should point to the end if element was not found!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d.find(1), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayMethods, FindAll) {
  int *int_array = new int[]{2, 2, 3, 3, 1};
  DynamicArray<int> d(5, int_array);

  std::vector<Iterator<int>> iterators{d.begin(), d.begin() + 1};
  std::vector<Iterator<int>> f = d.find_all(2);

  for (int i = 0; i < f.size(); i++) {
    EXPECT_EQ(f[i].get_index(), iterators[i].get_index())
        << "Indexes of found iterators should be equal!";
    EXPECT_EQ(*(f[i]), *(iterators[i]))
        << "Values of found iterators should be equal!";
  }

  std::vector<Iterator<int>> not_found;
  f = d.find_all(99);

  EXPECT_EQ(f.size(), 0) << "Vector of not found values must be 0!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d.find_all(99), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayMethods, FindIf) {
  int *int_array = new int[]{1, 2, 3, 4, 5, 6};
  DynamicArray<int> d(5, int_array);

  Iterator<int> it = d.begin();
  std::vector<Iterator<int>> iterators{it + 1, it + 3, it + 5};
  std::vector<Iterator<int>> f = d.find_if([](int x) { return x % 2 == 0; });

  for (int i = 0; i < f.size(); i++) {
    EXPECT_EQ(f[i].get_index(), iterators[i].get_index())
        << "Indexes of found iterators should be equal!";
    EXPECT_EQ(*(f[i]), *(iterators[i]))
        << "Values of found iterators should be equal!";
  }

  std::vector<Iterator<int>> not_found;
  f = d.find_if([](int x) { return x < 0; });

  EXPECT_EQ(f.size(), 0) << "Vector of not found values must be 0!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d.find_if([](int x) { return x > 0; }), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayMethods, ReplaceOccurence) {
  int *int_array = new int[]{1, 2, 3, 4, 5};
  DynamicArray<int> d(5, int_array);

  int *new_array = new int[]{1, 2, 99, 4, 5};
  d.replace(3, 99);

  for (int i = 0; i < 5; i++)
    EXPECT_EQ(d[i], new_array[i]) << "Values of arrays must be equal!";

  EXPECT_THROW(d.replace(100, 2), std::invalid_argument)
      << "Should throw invalid_argument if element is not found!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d.replace(1, 99), std::length_error)
      << "Should throw length error if array is empty!";
}

TEST(DynamicArrayMethods, ReplaceIterator) {
  int *int_array = new int[]{1, 2, 3, 4, 5};
  DynamicArray<int> d(5, int_array);

  Iterator<int> it = d.begin();
  int *new_array = new int[]{1, 2, 99, 4, 5};
  d.replace(it + 2, 99);

  for (int i = 0; i < 5; i++)
    EXPECT_EQ(d[i], new_array[i]) << "Values of arrays must be equal!";

  EXPECT_THROW(d.replace(it + 100, 2), std::out_of_range)
      << "Should throw out_of_range if iterator is not valid!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d.replace(it, 99), std::length_error)
      << "Should throw length error if array is empty!";
}

TEST(DynamicArrayMethods, ReplaceAll) {
  int *int_array = new int[]{2, 2, 3, 3, 4};
  DynamicArray<int> d(5, int_array);

  int *new_array = new int[]{2, 2, 99, 99, 4};
  d.replace_all(3, 99);

  for (int i = 0; i < 5; i++)
    EXPECT_EQ(d[i], new_array[i]) << "Values of arrays must be equal!";

  EXPECT_THROW(d.replace_all(100, 2), std::invalid_argument)
      << "Should throw invalid_argument if element is not found!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d.replace_all(1, 99), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayMethods, ReplaceIf) {
  int size = 6;
  std::string *str_array =
      new std::string[size]{"abc", "cba", "string", "string", "qwe", "zxcv"};
  DynamicArray<std::string> d(size, str_array);

  std::string *new_array =
      new std::string[size]{"X", "X", "string", "string", "X", "zxcv"};

  d.replace_if([](std::string str) { return str.size() == 0; }, "X");
  for (int i = 0; i < size; i++)
    EXPECT_EQ(d[i], str_array[i])
        << "Values should not change, nothing satifies the condition!";

  d.replace_if([](std::string str) { return str.size() <= 3; }, "X");

  for (int i = 0; i < 5; i++)
    EXPECT_EQ(d[i], new_array[i]) << "Values of arrays must be equal!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(
      d.replace_if([](std::string str) { return str.size() > 5; }, "X"),
      std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayMethods, ToVector) {
  DynamicArray<char> d(10);

  d.push_back('a');
  d.push_back('b');
  d.push_back('c');

  std::vector<char> dvec = d.to_vector();
  for (int i = 0; i < d.get_size(); i++)
    EXPECT_EQ(d[i], dvec[i])
        << "Elements of array and vector should be equal to each other!";
}

TEST(DynamicArrayMethods, FromVector) {
  std::vector<char> vec;

  vec.push_back('a');
  vec.push_back('b');
  vec.push_back('c');

  DynamicArray<char> d = DynamicArray<char>::from_vector(vec);
  EXPECT_EQ(vec.size(), d.get_size())
      << "Vector and dynamic array sizes should be equal!";

  for (int i = 0; i < d.get_size(); i++)
    EXPECT_EQ(d[i], vec[i])
        << "Elements of array and vector should be equal to each other!";
}

TEST(DynamicArrayMethods, ToString) {
  DynamicArray<char> d(10);

  d.push_back('a');
  d.push_back('b');
  d.push_back('c');

  std::string str = d.to_string();
  std::string res = "a, b, c.";
  EXPECT_EQ(str, res) << "String should be equal to each other!";
}

// ----------
// Useful functions test
// ----------

TEST(DynamicArrayUsefulFunctions, CountElement) {
  std::vector<char> vec{'a', 'b', 'c', 'a', 'x', 'b', 'b', 'x'};
  DynamicArray<char> d(vec);

  char el = 'b';
  int count = d.count(el);

  EXPECT_EQ(count, 3) << "Number of elements should be equal to 3";

  el = 'x';
  count = d.count(el);
  EXPECT_NE(count, 0) << "Number of elements should be more than 0.";

  el = 'd';
  count = d.count(el);
  EXPECT_EQ(count, 0) << "There are no elements: " << el;
}

TEST(DynamicArrayUsefulFunctions, CountIf) {
  std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
  DynamicArray<int> d(vec);

  int count = d.count_if([](int x) { return x % 2 == 0; });
  EXPECT_EQ(count, 4) << "Number of even elements should be 4!";

  count = d.count_if([](int x) { return x % 2 != 0; });
  EXPECT_EQ(count, 5) << "Number of odd elements should be 5!";

  count = d.count_if([](int x) { return x < 0; });
  EXPECT_EQ(count, 0) << "There are no elemets that are < 0!";
}

TEST(DynamicArrayUsefulFunctions, Filter) {
  std::vector<std::string> vec{"abc",    "cde",   "drf",   "qwe",
                               "qwerty", "ghjjt", "nfwje", "akjskg"};
  DynamicArray<std::string> d(vec);

  std::vector<std::string> filter_vec = {"abc", "cde", "drf", "qwe"};
  DynamicArray<std::string> filtered1 =
      d.filter([](std::string str) { return str.size() == 3; });

  EXPECT_EQ(filtered1.get_size(), filter_vec.size())
      << "Size of filtered array should be: " << filter_vec.size();

  for (int i = 0; i < filtered1.get_size(); i++)
    EXPECT_EQ(filtered1[i], filter_vec[i])
        << "Values of arrays should be equal!";

  DynamicArray<std::string> filtered2 =
      filtered1.filter([](std::string str) { return str.size() > 3; });

  EXPECT_EQ(filtered2.get_size(), filtered1.get_size())
      << "If nothing was found, should return array itself!";

  for (int i = 0; i < filtered2.get_size(); i++)
    EXPECT_EQ(filtered2[i], filtered1[i]) << "Nothing should change!";

  filtered2.erase_range(filtered2.begin(), filtered2.end());
  EXPECT_THROW(
      filtered2.filter([](std::string str) { return str.size() == 0; }),
      std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayUsefulFunctions, Map) {
  std::vector<float> vec{1.2, 2.4, 3.6, 4.8, 5.0};
  DynamicArray<float> d(vec);

  d.map([](float x) { std::cout << x << " "; });

  std::vector<float> results;
  d.map([&results](float x) { results.push_back(x * 2); });

  std::vector<float> expected = {2.4, 4.8, 7.2, 9.6, 10.0};
  EXPECT_EQ(results, expected);

  for (int i = 0; i < results.size(); i++) {
    EXPECT_NE(vec[i], results[i]) << "Values should not be equal!";
    EXPECT_EQ(expected[i], results[i]);
  }

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d.map([](float x) { std::cout << x << " "; }), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayUsefulFunctions, Apply) {
  std::vector<int> vec{6, 12, 24, 10, 50};
  DynamicArray<int> d1(vec);

  d1 = d1.apply([](int x) { return x / 2; });
  std::vector<int> expected{3, 6, 12, 5, 25};

  for (int i = 0; i < expected.size(); i++)
    EXPECT_EQ(d1[i], expected[i])
        << "Values of expected and resulting arrays should be equal!";

  std::vector<std::string> strings{"hello", "world", "abc"};
  DynamicArray<std::string> d2(strings);

  d2 = d2.apply([](std::string str) {
    if (!str.empty())
      str[0] = std::toupper(str[0]);

    return str;
  });

  std::vector<std::string> expected_strs{"Hello", "World", "Abc"};
  for (int i = 0; i < expected_strs.size(); i++)
    EXPECT_EQ(d2[i], expected_strs[i])
        << "Values of expected and resulting arrays should be equal!";

  d1.erase_range(d1.begin(), d1.end());
  EXPECT_THROW(d1.apply([](int x) { return x * 2; }), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayUsefulFunctions, Reduce) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  DynamicArray<int> d(vec);

  int sum = d.reduce(0);
  int expected = std::accumulate(vec.begin(), vec.end(), 0);

  EXPECT_EQ(sum, expected)
      << "Values of the sum and expected sum should be equal!";

  int mult = d.reduce(0, [](int x, int y) { return x * y; });
  expected = std::accumulate(vec.begin(), vec.end(), 0,
                             [](int x, int y) { return x * y; });

  EXPECT_EQ(mult, expected)
      << "Values of the multiplication results and expected should be equal!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d.reduce(0), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayUsefulFunctions, Reverse) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  DynamicArray<int> d1(vec);

  std::vector<int> expected{5, 4, 3, 2, 1};
  d1.reverse();

  for (int i = 0; i < d1.get_size(); i++)
    EXPECT_EQ(d1[i], expected[i])
        << "Values of array and expected values should be equal!";

  DynamicArray<int> d2 = d1.reversed();
  EXPECT_EQ(d2.get_size(), vec.size()) << "Sizes should be equal!";

  for (int i = 0; i < d2.get_size(); i++)
    EXPECT_EQ(d2[i], vec[i])
        << "Values of array should be equal to initial vector values!";

  d1.erase_range(d1.begin(), d1.end());
  EXPECT_THROW(d1.reverse(), std::length_error)
      << "Should throw length_error if array is empty!";
  EXPECT_THROW(d1 = d1.reversed(), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayUsefulFunctions, ReversePartial) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  DynamicArray<int> d(vec);

  Iterator<int> it = d.begin();
  std::vector<int> expected{1, 4, 3, 2, 5};

  EXPECT_THROW(d.reverse_partial(it - 99, it + 1), std::out_of_range)
      << "Should throw out_of_range!";
  EXPECT_THROW(d.reverse_partial(it + 1, it + 99), std::out_of_range)
      << "Should throw out_of_range!";
  EXPECT_THROW(d.reverse_partial(it + 3, it + 1), std::invalid_argument)
      << "it1 should be less than it2!";

  d.reverse_partial(it + 1, it + 3);
  for (int i = 0; i < d.get_size(); i++)
    EXPECT_EQ(d[i], expected[i])
        << "Values of array and expected should be equal!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d.reverse_partial(it + 1, it + 3), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayUsefulFunctions, RemoveDuplicates) {
  std::vector<char> vec{'a', 'a', 'b', 'b', 'c'};
  DynamicArray<char> d(vec);

  d = d.remove_duplicates();
  std::vector<char> expected{'a', 'b', 'c'};

  for (int i = 0; i < d.get_size(); i++)
    EXPECT_EQ(d[i], expected[i])
        << "Values of array and expected should be equal!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d = d.remove_duplicates(), std::length_error)
      << "Should throw length_error if array is empty!";
}
