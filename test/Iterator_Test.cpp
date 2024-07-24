#include <Iterator.h>
#include <gtest/gtest.h>

#include <stdexcept>

// ----------
// Constructors test
// ----------

TEST(IteratorConstructors, ArrayBasedConstructor) {
  int index = 0, size = 3;
  int *int_array = new int[size]{1, 2, 3};
  Iterator<int> it1(int_array);

  EXPECT_TRUE(Iterator<int>::is_valid(it1, size))
      << "The provided iterator should be valid!";

  EXPECT_EQ(it1.get_index(), index) << "Index should be equal: " << index;
  for (int i = 0; i < 3; i++)
    EXPECT_EQ(it1.get_iterable()[i], int_array[i])
        << "Values of array should be equal!";

  index = -99;
  EXPECT_THROW(Iterator<int> it2(int_array, index), std::out_of_range)
      << "Should throw out_of_range because index is negative!";
}

TEST(IteratorConstructors, CopyConstructor) {
  int index = 0, size = 3;
  int *int_array = new int[size]{1, 2, 3};
  Iterator<int> it1(int_array);

  EXPECT_TRUE(Iterator<int>::is_valid(it1, size))
      << "The provided iterator should be valid!";

  Iterator<int> it2(it1);
  EXPECT_EQ(it2.get_index(), it1.get_index())
      << "Indexes should be equal: " << it1.get_index();

  for (int i = 0; i < size; i++)
    EXPECT_EQ(it2.get_iterable()[i], it1.get_iterable()[i])
        << "Values should be equal!";

  index = -99;
  EXPECT_THROW(Iterator<int> it4(Iterator<int>(int_array, index)),
               std::out_of_range)
      << "Should throw out_of_range because index is negative!";
}

// ----------
// Getters test
// ----------

TEST(IteratorGetters, GetIterable) {
  int *int_array = new int[]{1, 2, 3};
  Iterator<int> it(int_array, 0);

  EXPECT_EQ(it.get_iterable(), int_array) << "Should return int array!";
}

TEST(IteratorGetters, GetIndex) {
  int *int_array = new int[]{1, 2, 3};
  Iterator<int> it(int_array, 2);

  EXPECT_EQ(it.get_index(), 2) << "Should return index 2!";
}

TEST(IteratorGetters, Size) {
  int *int_array = new int[]{1, 2, 3};
  Iterator<int> it(int_array, 2);

  EXPECT_EQ(it.get_size(), 3) << "Should return size 3!";
}

// ----------
// Methods test
// ----------

TEST(IteratorMethods, IsValid) {
  int *int_array = new int[]{1, 2, 3};
  Iterator<int> it(int_array, 2);

  EXPECT_TRUE(Iterator<int>::is_valid(it, 3)) << "Should return true!";
  EXPECT_FALSE(Iterator<int>::is_valid(it, 0)) << "Should return false!";
}

TEST(IteratorMethods, IncrementOperator) {
  int *int_array = new int[]{1, 2, 3};
  Iterator<int> it(int_array, 0);
  ++it;

  EXPECT_EQ(it.get_index(), 1) << "Should be at 2nd element!";
}

TEST(IteratorMethods, DereferenceOperator) {
  int *int_array = new int[]{1, 2, 3, 4, 5, 6};
  Iterator<int> it(int_array, 2);

  EXPECT_EQ(*it, 3) << "Should return element of index 3!";
}

TEST(IteratorMethods, AdditionOperator) {
  int *int_array = new int[]{1, 2, 3, 4, 5, 6, 7};
  Iterator<int> it(int_array, 1);
  auto it2 = it + 2;

  EXPECT_EQ(it2.get_index(), 3) << "Index should be 3!";
  EXPECT_THROW(it + (-2), std::out_of_range)
      << "Should throw out_of_range exception!";
}

TEST(IteratorMethods, SubtractionOperator) {
  int *int_array = new int[]{1, 2, 3, 4, 5, 6, 7};
  Iterator<int> it(int_array, 3);
  auto it2 = it - 2;

  EXPECT_EQ(it2.get_index(), 1) << "Should be at 2nd element!";
  EXPECT_THROW(it - 4, std::out_of_range)
      << "Should throw out_of_range exception!";
}

// ----------
// Operators test
// ----------

TEST(IteratorOperators, EqualityOperator) {
  int *int_array = new int[]{1, 2, 3, 4, 5};
  Iterator<int> it1(int_array, 2);
  Iterator<int> it2(int_array, 2);

  EXPECT_TRUE(it1 == it2) << "Iterators it1 and it2 should be equal!";
}

TEST(IteratorOperators, InequalityOperator) {
  int *int_array = new int[]{1, 2, 3, 4, 5};
  Iterator<int> it1(int_array, 2);
  Iterator<int> it2(int_array, 3);

  EXPECT_TRUE(it1 != it2) << "Iterators it1 and it2 should not be equal!";
}

TEST(IteratorOperators, LessThan) {
  int *int_array = new int[]{1, 2, 3, 4, 5};
  Iterator<int> it1(int_array, 2);
  Iterator<int> it2(int_array, 3);

  EXPECT_TRUE(it1 < it2) << "Iterator it1 should be less than it2!";
}

TEST(IteratorTest, GreaterThan) {
  int *int_array = new int[]{1, 2, 3, 4, 5};
  Iterator<int> it1(int_array, 3);
  Iterator<int> it2(int_array, 2);

  EXPECT_TRUE(it1 > it2) << "Iterator it1 should be greater than it2!";
}
