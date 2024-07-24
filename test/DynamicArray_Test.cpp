#include <DynamicArray.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <sys/errno.h>

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

  EXPECT_EQ(d.get_size(), size);
  EXPECT_EQ(d.get_capacity(), size);

  for (int i = 0; i < size; i++)
    EXPECT_EQ(int_array[i], d[i]) << "Should be equal to each other ("
                                  << int_array[i] << " = " << d[i] << ").";
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
