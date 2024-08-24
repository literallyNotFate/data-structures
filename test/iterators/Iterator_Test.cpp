#include <Iterator.h>
#include <gtest/gtest.h>

#include <stdexcept>

// ----------
// Constructors test
// ----------

TEST(IteratorConstructors, ArrayBasedConstructor) {
  int index = 0, size = 3;
  int *int_array = new int[size]{1, 2, 3};
  Iterator<int> it1(int_array, size);

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
  Iterator<int> it1(int_array, size);

  Iterator<int> it2(it1);
  EXPECT_EQ(it2.get_index(), it1.get_index())
      << "Indexes should be equal: " << it1.get_index();

  for (int i = 0; i < size; i++)
    EXPECT_EQ(it2.get_iterable()[i], it1.get_iterable()[i])
        << "Values should be equal!";

  index = -99;
  EXPECT_THROW(Iterator<int> it4(Iterator<int>(int_array, size, index)),
               std::out_of_range)
      << "Should throw out_of_range because index is negative!";
}

// ----------
// Getters test
// ----------

TEST(IteratorGetters, GetIterable) {
  int size = 3;
  int *int_array = new int[size]{1, 2, 3};
  Iterator<int> it(int_array, size);

  EXPECT_EQ(it.get_iterable(), int_array) << "Should return int array!";
}

TEST(IteratorGetters, GetIndex) {
  int size = 3;
  int *int_array = new int[size]{1, 2, 3};
  Iterator<int> it(int_array, size, 2);

  EXPECT_EQ(it.get_index(), 2) << "Should return index 2!";
}

// ----------
// Methods test
// ----------

TEST(IteratorMethods, IncrementOperator) {
  int size = 3;
  int *int_array = new int[size]{1, 2, 3};
  Iterator<int> it(int_array, size);
  ++it;

  EXPECT_EQ(it.get_index(), 1) << "Should be at 2nd element!";
}

TEST(IteratorMethods, DecrementOperator) {
  int size = 3;
  int *int_array = new int[size]{1, 2, 3};
  Iterator<int> it(int_array, size, size);
  --it;

  EXPECT_EQ(it.get_index(), 2) << "Should be at 2nd element!";
}

TEST(IteratorMethods, DereferenceOperator) {
  int size = 6;
  int *int_array = new int[size]{1, 2, 3, 4, 5, 6};
  Iterator<int> it(int_array, size, 2);

  EXPECT_EQ(*it, 3) << "Should return element of index 3!";
}

TEST(IteratorMethods, ArrowOperator) {
  class Person {
  public:
    const char *name;
    int age;

    Person() : name("Default"), age(0) {};
    Person(const char *name, int age) : name(name), age(age) {};
  };

  int size = 3;
  Person *person_array = new Person[size]{
      Person("John", 20), Person("Mike", 19), Person("Kyle", 15)};
  Iterator<Person> it(person_array, size);

  int *ages = new int[size]{20, 19, 15};
  const char **names = new const char *[size] { "John", "Mike", "Kyle" };

  for (int i = 0; i < size; ++i, ++it) {
    EXPECT_EQ(it->name, names[i]) << "Names should be equal!";
    EXPECT_EQ(it->age, ages[i]) << "Ages should be equal!";
  }
}

TEST(IteratorMethods, AdditionOperator) {
  int size = 7;
  int *int_array = new int[size]{1, 2, 3, 4, 5, 6, 7};
  Iterator<int> it(int_array, size, 1);
  auto it2 = it + 2;

  EXPECT_EQ(it2.get_index(), 3) << "Index should be 3!";
  EXPECT_THROW(it + (-2), std::out_of_range)
      << "Should throw out_of_range exception!";
}

TEST(IteratorMethods, SubtractionOperator) {
  int size = 7;
  int *int_array = new int[size]{1, 2, 3, 4, 5, 6, 7};
  Iterator<int> it(int_array, size, 3);
  auto it2 = it - 2;

  EXPECT_EQ(it2.get_index(), 1) << "Should be at 2nd element!";
  EXPECT_THROW(it - 4, std::out_of_range)
      << "Should throw out_of_range exception!";
}

TEST(IteratorMethods, Advance) {
  int size = 3;
  int *int_array = new int[size]{10, 20, 30};
  Iterator<int> it(int_array, size);

  Iterator<int>::advance(it, 2);
  EXPECT_EQ(it.get_index(), size - 1)
      << "Iterator should be pointing at the end!";

  Iterator<int>::advance(it, 5);
  EXPECT_EQ(it.get_index(), size - 1)
      << "Iterator should still be pointing at the end!";

  Iterator<int>::advance(it, -10);
  EXPECT_EQ(it.get_index(), 0) << "Iterator should be at the beginning!";
}

// ----------
// Compare test
// ----------

TEST(IteratorCompare, EqualityOperator) {
  int size = 5;
  int *int_array = new int[size]{1, 2, 3, 4, 5};
  Iterator<int> it1(int_array, size, 2);
  Iterator<int> it2(int_array, size, 2);

  EXPECT_TRUE(it1 == it2) << "Iterators it1 and it2 should be equal!";
}

TEST(IteratorCompare, InequalityOperator) {
  int size = 5;
  int *int_array = new int[size]{1, 2, 3, 4, 5};
  Iterator<int> it1(int_array, size, 2);
  Iterator<int> it2(int_array, size, 3);

  EXPECT_TRUE(it1 != it2) << "Iterators it1 and it2 should not be equal!";
}

TEST(IteratorCompare, LessThan) {
  int size = 5;
  int *int_array = new int[size]{1, 2, 3, 4, 5};
  Iterator<int> it1(int_array, size, 2);
  Iterator<int> it2(int_array, size, 3);

  EXPECT_TRUE(it1 < it2) << "Iterator it1 should be less than it2!";
  EXPECT_TRUE(it1 <= it2) << "Iterator it1 should be less or equal than it2!";
}

TEST(IteratorCompare, GreaterThan) {
  int size = 5;
  int *int_array = new int[size]{1, 2, 3, 4, 5};
  Iterator<int> it1(int_array, size, 3);
  Iterator<int> it2(int_array, size, 2);

  EXPECT_TRUE(it1 > it2) << "Iterator it1 should be greater than it2!";
  EXPECT_TRUE(it1 >= it2)
      << "Iterator it1 should be greater or equal than it2!";
}
