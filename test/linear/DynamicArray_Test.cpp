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

TEST(DynamicArrayConstructors, RangeBasedConstructor) {
  std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  DynamicArray<int> d(vec.begin(), vec.end());

  EXPECT_EQ(d.get_size(), vec.size())
      << "Dynamic array size should be based vector size: " << vec.size();
  EXPECT_EQ(d.get_capacity(), vec.size())
      << "Dynamic array capacity should be based vector size: " << vec.size();

  for (int i = 0; i < vec.size(); i++)
    EXPECT_EQ(d[i], vec[i])
        << "Should be equal to each other (" << d[i] << " = " << vec[i] << ").";

  EXPECT_THROW(DynamicArray<int> d1(vec.end(), vec.begin()),
               std::invalid_argument)
      << "Should throw invalid_argument if first iterator is greater than the "
         "second!";
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
// Compare tests
// ----------

TEST(DynamicArrayCompare, GreaterThan) {
  int *int_array1 = new int[]{1, 2, 3}, *int_array2 = new int[]{4, 5, 6};
  DynamicArray<int> d1(3, int_array1), d2(2, int_array1), d3(3, int_array2);

  EXPECT_TRUE(d1 > d2) << "d1 should be greater than d2 (" << d1.get_size()
                       << " > " << d2.get_size() << ").";

  EXPECT_FALSE(d1 > d1) << "Should return false because arrays are equal!";
  EXPECT_FALSE(d1 > d3)
      << "Should return true because ALL values of d3 > ALL values of d1.";
}

TEST(DynamicArrayCompare, LessThan) {
  int *int_array1 = new int[]{1, 2, 3}, *int_array2 = new int[]{4, 5, 6};
  DynamicArray<int> d1(3, int_array1), d2(2, int_array1), d3(3, int_array2);

  EXPECT_TRUE(d2 < d1) << "d2 should be less than d1 (" << d2.get_size()
                       << " < " << d1.get_size() << ").";

  EXPECT_FALSE(d1 < d1) << "Should return false because arrays are equal!";
  EXPECT_FALSE(d3 < d1)
      << "Should return true because ALL values of d1 < ALL values of d3.";
}

TEST(DynamicArrayCompare, EqualityOperator) {
  DynamicArray<int> d1(3, 0), d2(3, 0), d3(3, 1);

  EXPECT_TRUE(d1 == d2) << "d1 and d2 should be equal!";
  EXPECT_FALSE(d1 == d3) << "d1 and d3 should not be equal!";
}

TEST(DynamicArrayCompare, InequalityOperator) {
  DynamicArray<int> d1(3, 0), d2(3, 0), d3(3, 1);

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
  DynamicArray<int> d(6);

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

  d.push_begin(40);
  EXPECT_THROW(d.insert(index, value), std::length_error)
      << "Should throw length_error if array is full!";
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
  EXPECT_FALSE(d.contains(2)) << "Deleted element should not be in the array !";

  d.erase_back();

  EXPECT_TRUE(d.is_empty())
      << "Array must be empty after deleting everything !";
  EXPECT_THROW(d.erase_back(), std::length_error)
      << "Should throw length_error, because there are no elements to delete !";
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
  EXPECT_FALSE(d.contains(1)) << "Deleted element should not be in the array !";

  d.erase_begin();

  EXPECT_TRUE(d.is_empty())
      << "Array must be empty after deleting everything !";
  EXPECT_THROW(d.erase_back(), std::length_error)
      << "Should throw length_error, because there are no elements to delete !";
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

  EXPECT_FALSE(d.contains(2)) << "Deleted element (2) should not be in array !";
  EXPECT_FALSE(d.contains(3)) << " Deleted element(3) should not be in array !";
  EXPECT_FALSE(d.contains(4)) << " Deleted element(4) should not be in array !";
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

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d.erase_all(1), std::length_error)
      << "Should throw lenghh error if array is empty!";
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
  int size1 = 3, size2 = 5;
  DynamicArray<int> d1(size1, 1), d2(size2, 0);

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
  std::string s1 = "abc", s2 = "abs";
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

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d[0], std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayMethods, Find) {
  int *int_array = new int[]{1, 2, 3, 4, 5};
  DynamicArray<int> d(5, int_array);

  Iterator<int> f = d.find(1);
  EXPECT_EQ(*f, *(d.begin())) << "Iterator should point at index 0!";
  EXPECT_EQ((d.find(5) - 1).get_index(), 3)
      << "Should point to the previous index of the found element at the send.";
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
  EXPECT_EQ(str, res) << "Strings should be equal to each other!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(str = d.to_string(), std::length_error)
      << "Should throw length_error if array is empty!";
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

TEST(DynamicArrayUsefulFunctions, FrequencyMap) {
  std::vector<int> vec{1, 2, 1, 2, 3, 4, 1, 5, 6, 7, 7, 8, 9, 9};
  DynamicArray<int> d(vec);

  std::map<int, int> freq = d.frequency_map();
  std::map<int, int> expected = {{1, 3}, {2, 2}, {3, 1}, {4, 1}, {5, 1},
                                 {6, 1}, {7, 2}, {8, 1}, {9, 2}};

  EXPECT_EQ(freq.size(), expected.size())
      << "Sizes of frequency map and expected should be equal!";

  for (std::map<int, int>::iterator it1 = freq.begin(), it2 = expected.begin();
       it1 != freq.end(); ++it1, ++it2) {
    EXPECT_EQ(it1->first, it2->first) << "Keys/numbers should be equal!";
    EXPECT_EQ(it1->second, it2->second) << "Count numbers should be equal!";
  }

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(d.frequency_map(), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayUsefulFunctions, Swap) {
  std::vector<int> vec1{1, 2, 3}, vec2{4, 5, 6, 7};
  DynamicArray<int> d1(vec1), d2(vec2);

  EXPECT_EQ(d1.get_size(), vec1.size()) << "First array should be sized 3!";
  EXPECT_EQ(d2.get_size(), vec2.size()) << "Second array should be sized 4!";

  DynamicArray<int>::swap(d1, d2);

  EXPECT_EQ(d1.get_size(), vec2.size())
      << "First array after swapping should be sized 4!";
  EXPECT_EQ(d2.get_size(), vec1.size())
      << "Second array after swapping should be sized 3!";

  for (int i = 0; i < vec2.size(); i++)
    EXPECT_EQ(d1[i], vec2[i]) << "Values should be equal!";

  for (int i = 0; i < vec1.size(); i++)
    EXPECT_EQ(d2[i], vec1[i]) << "Values should be equal!";
}

// ----------
// Finding min/max test
// ----------

TEST(DynamicArrayMinMax, Min) {
  std::vector<int> vec1{1, 2, 3, -10, 5};
  DynamicArray<int> d1(vec1);

  int min = d1.min(), expected = -10;
  EXPECT_EQ(min, expected) << "Values of min and expected min should be equal!";

  d1.erase_range(d1.begin(), d1.end());
  EXPECT_THROW(d1.min(), std::length_error)
      << "Should throw length_error if array is empty!";

  std::vector<std::string> vec2{"abc", "hello", "world", "hi",
                                "g",   "1234",  "14"};
  DynamicArray<std::string> d2(vec2);
  std::string min_size = d2.min([](std::string str) { return str.size(); }),
              min_expected = "g";

  EXPECT_EQ(min_size, min_expected)
      << "Values of min and expected min should be equal!";

  d2.erase_range(d2.begin(), d2.end());
  EXPECT_THROW(d2.min([](std::string str) { return str.size(); }),
               std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArrayMinMax, Max) {
  std::vector<int> vec1{1, 2, 3, -10, 5};
  DynamicArray<int> d1(vec1);

  int min = d1.max(), expected = 5;
  EXPECT_EQ(min, expected) << "Values of max and expected max should be equal!";

  d1.erase_range(d1.begin(), d1.end());
  EXPECT_THROW(d1.max(), std::length_error)
      << "Should throw length_error if array is empty!";

  std::vector<std::string> vec2{"abc", "hello", "world", "hi",
                                "g",   "1234",  "14"};
  DynamicArray<std::string> d2(vec2);
  std::string max_size = d2.max([](std::string str) { return str.size(); }),
              max_expected = "hello";

  EXPECT_EQ(max_size, max_expected)
      << "Values of max and expected max should be equal!";

  d2.erase_range(d2.begin(), d2.end());
  EXPECT_THROW(d2.max([](std::string str) { return str.size(); }),
               std::length_error)
      << "Should throw length_error if array is empty!";
}

// ----------
// Sorting test
// ----------

TEST(DynamicArraySorting, BubbleSort) {
  std::vector<int> vec1{6, 4, 8, 12, 5, 5, -1, 0, 5, 2, 1};
  DynamicArray<int> d1(vec1);

  d1.bubble_sort();
  std::vector<int> expected1{-1, 0, 1, 2, 4, 5, 5, 5, 6, 8, 12};

  for (int i = 0; i < d1.get_size(); i++)
    EXPECT_EQ(d1[i], expected1[i])
        << "Array must be sorted in ascending order!";

  std::vector<int> vec2{12, 5, 15, 20, 30, 43, 100, 20, -12, -20};
  DynamicArray<int> d2(vec2);

  d2.bubble_sort([](int x, int y) { return x > y; });
  std::vector<int> expected2{100, 43, 30, 20, 20, 15, 12, 5, -12, -20};

  for (int i = 0; i < d2.get_size(); i++)
    EXPECT_EQ(d2[i], expected2[i])
        << "Array must be sorted in descending order!";

  d2.erase_range(d2.begin(), d2.end());
  EXPECT_THROW(d2.bubble_sort(), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArraySorting, SelectionSort) {
  std::vector<std::string> vec{"abc", "hello", "123456", "world", "A", "hi"};
  DynamicArray<std::string> d1(vec);

  d1.selection_sort(
      [](std::string x, std::string y) { return x.size() < y.size(); });
  std::vector<std::string> expected1{"A",     "hi",    "abc",
                                     "world", "hello", "123456"};

  for (int i = 0; i < d1.get_size(); i++)
    EXPECT_EQ(d1[i], expected1[i])
        << "Array must be sorted by strings size in ascending order!";

  DynamicArray<std::string> d2(vec);
  d2.selection_sort(
      [](std::string x, std::string y) { return x.size() > y.size(); });

  std::vector<std::string> expected2{"123456", "hello", "world",
                                     "abc",    "hi",    "A"};

  for (int i = 0; i < d2.get_size(); i++)
    EXPECT_EQ(d2[i], expected2[i])
        << "Array must be sorted in descending order!";

  d2.erase_range(d2.begin(), d2.end());
  EXPECT_THROW(d2.selection_sort(), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArraySorting, MergeSort) {
  class Person {
  public:
    const char *name;
    int age;

    Person() : name("Default"), age(0) {};
    Person(const char *name, int age) : name(name), age(age) {};

    inline bool operator<(const Person &other) const {
      return this->age < other.age;
    }
    inline bool operator>(const Person &other) const {
      return this->age > other.age;
    }
  };

  std::vector<Person> vec{Person("Jake", 20), Person("Mark", 18),
                          Person("Rick", 16), Person("Kyle", 22),
                          Person("Joe", 27)};

  DynamicArray<Person> d1(vec);
  d1.merge_sort();

  std::vector<Person> expected1{Person("Rick", 16), Person("Mark", 18),
                                Person("Jake", 20), Person("Kyle", 22),
                                Person("Joe", 27)};

  for (int i = 0; i < d1.get_size(); i++) {
    EXPECT_EQ((std::string)d1[i].name, (std::string)expected1[i].name)
        << "Names should be equal after sorting in ascending order!";
    EXPECT_EQ(d1[i].age, expected1[i].age)
        << "Ages should be equal after sorting in ascending order!";
  }

  DynamicArray<Person> d2(vec);
  d2.merge_sort(std::greater<Person>());

  std::vector<Person> expected2{Person("Joe", 27), Person("Kyle", 22),
                                Person("Jake", 20), Person("Mark", 18),
                                Person("Rick", 16)};

  for (int i = 0; i < d2.get_size(); i++) {
    EXPECT_EQ((std::string)d2[i].name, (std::string)expected2[i].name)
        << "Names should be equal after sorting in descending order!";
    EXPECT_EQ(d2[i].age, expected2[i].age)
        << "Ages should be equal after sorting in descending order!";
  }

  d2.erase_range(d2.begin(), d2.end());
  EXPECT_THROW(d2.merge_sort(), std::length_error)
      << "Should throw length_error if array is empty!";
}

// ----------
// Set operations
// ----------

TEST(DynamicArraySetOperations, Merge) {
  DynamicArray<int> d1(3, 0), d2(5, 1);

  DynamicArray<int> result = d1 + d2;
  std::vector<int> expected{0, 0, 0, 1, 1, 1, 1, 1};

  EXPECT_EQ(result.get_size(), expected.size())
      << "New size should be: d1.size() + d2.size().";

  for (int i = 0; i < result.get_size(); i++)
    EXPECT_EQ(result[i], expected[i]) << "Value should be equal!";

  d1.erase_range(d1.begin(), d1.end());
  EXPECT_THROW(DynamicArray<int> res = d1 + d2, std::length_error)
      << "Should throw length_error if one of the arrays is empty!";

  d2.erase_range(d2.begin(), d2.end());
  EXPECT_THROW(DynamicArray<int> res = d1 + d2, std::length_error)
      << "Should throw length_error if one of the arrays is empty!";
}

TEST(DynamicArraySetOperations, Union) {
  std::vector<int> vec1{1, 2, 2, 3, 3}, vec2{1, 2, 3, 4, 3, 2};

  DynamicArray<int> d1(vec1), d2(vec2);
  DynamicArray<int> result = d1 | d2;

  std::vector<int> expected{1, 2, 3, 4};
  for (int i = 0; i < result.get_size(); i++)
    EXPECT_EQ(result[i], expected[i]) << "Values should be equal!";

  d1.erase_range(d1.begin(), d1.end());
  EXPECT_THROW(DynamicArray<int> res = d1 | d2, std::length_error)
      << "Should throw length_error if one of the arrays is empty!";

  d2.erase_range(d2.begin(), d2.end());
  EXPECT_THROW(DynamicArray<int> res = d1 | d2, std::length_error)
      << "Should throw length_error if one of the arrays is empty!";
}

TEST(DynamicArraySetOperations, Intersection) {
  std::vector<int> vec1{1, 2, 2, 3, 3};
  std::vector<int> vec2{1, 2, 3, 4, 3, 2};

  DynamicArray<int> d1(vec1), d2(vec2);
  DynamicArray<int> result = d1 & d2;

  std::vector<int> expected{1, 2, 3};
  for (int i = 0; i < result.get_size(); i++)
    EXPECT_EQ(result[i], expected[i]) << "Values should be equal!";

  d1.erase_range(d1.begin(), d1.end());
  EXPECT_THROW(DynamicArray<int> res = d1 & d2, std::length_error)
      << "Should throw length_error if one of the arrays is empty!";

  d2.erase_range(d2.begin(), d2.end());
  EXPECT_THROW(DynamicArray<int> res = d1 & d2, std::length_error)
      << "Should throw length_error if one of the arrays is empty!";
}

// ----------
// Some functions test
// ----------

TEST(DynamicArraySome, Distinct) {
  std::vector<char> vec{'a', 'b', 'c', 'c', 'b', 'd', 'a'};
  DynamicArray<char> d(vec);

  Iterator<char> it = d.end();
  Iterator<char> dist = d.distinct(), expected = it - 1;

  EXPECT_EQ(dist.get_index(), expected.get_index())
      << "Indexes of found distinct and expected distinct should be equal!";
  EXPECT_EQ(*dist, *expected)
      << "Values of found distinct and expected distinct should be equal!";
  EXPECT_EQ(dist, Iterator<char>(expected, true)) << "Iterators must be equal!";

  d.erase_all('d');
  dist = d.distinct();

  EXPECT_EQ(dist, d.end())
      << "Distinct iterator must be equal to end() if nothing was found!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(dist = d.distinct(), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArraySome, KthDistinct) {
  std::vector<std::string> vec{"aaa", "aa", "a"};
  DynamicArray<std::string> d(vec);

  Iterator<std::string> it = d.begin();
  Iterator<std::string> kth = d.kth_distinct(2);

  EXPECT_EQ(kth, Iterator<std::string>(it + 1, true))
      << "2nd distinct element should be pointing to the "
         "2nd element of an array!";

  kth = d.kth_distinct(10);
  EXPECT_EQ(kth, d.end()) << "Should be equal to end() if nothing was found!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(kth = d.kth_distinct(3), std::length_error)
      << "Should throw length_error if array is empty!";
}

TEST(DynamicArraySome, TopKFrequent) {
  std::vector<int> vec{1, 1, 1, 2, 2, 3};
  DynamicArray<int> d(vec);

  std::vector<int> topk = d.top_k_frequent(2);
  std::vector<int> expected{1, 2};

  for (int i = 0; i < topk.size(); i++)
    EXPECT_EQ(topk[i], expected[i])
        << "Values of the topk and expected should be equal!";

  d.erase_range(d.begin(), d.end());
  EXPECT_THROW(topk = d.top_k_frequent(3), std::length_error)
      << "Should throw length_error if array is empty!";
}
