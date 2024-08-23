# Data structures

---

## Linear

1. **Dynamic Array** (collection of elements stored in **contiguous memory locations**.)
    * *Accessing* - **O(1)**
    * *Inserting* - **O(n)**, if appending to end - **O(1)**
    * *Deletion* - **O(n)**, if deleting last - **O(1)**
    * *Searching* - **O(n)** on unsorted, with sorted + BS - **O(logn)**

2. **Stack** (collection of elements with **Last-In-First-Out (LIFO)** order.)
    * *push()* - **O(1)**
    * *pop()* - **O(1)**
    * *peek()* - **O(1)**
    * *is_empty()* - **O(1)**

3. **Queue** (collection of elements with **First-In-First-Out (FIFO)** order.)
    * *enqueue()* - **O(1)**
    * *dequeue()* - **O(1)**
    * *peek()* - **O(1)**

4. **Linked List** (series of connected nodes, where each node stores the **data and the address of the next node**.)
    * *Inserting* - **O(n)**, if inserting at the beginning - **O(1)**
    * *Deletion* - **O(n)**, if deleting the first - **O(1)**
    * *Searching* - *O(n)*, if it is the first element - **O(1)**
    * *Traversal* - *O(n)*

## Non-linear

1. **Tree** (specialized data structure to store data in *hierarchical manner*.)

2. **Binary Tree** (each node can have at most two children which are referred to as the **left child and the right child**.)

3. **Binary Search Tree** (left child of a node has a value less than the node’s value and the **right child has a value greater than the node’s value**.)

4. **Graph** (set of **vertices (V) and a set of edges(E)**.)

---

# Quick Start

First, you need to copy GoogleTest (GTest) library into your project.
It must be located in the 'external' folder.

```bash
mkdir external
cd external
git clone https://github.com/google/googletest.git
```
Then, you have to build the project itself.
To build the project, follow these steps:

```bash
mkdir build
cd build
cmake ..
make
```
You are ready to run the tests!

---

# Running the Tests

There are two options:

## Through executable

**To run the tests through executable, use the following command:**

```bash
cd build/test
./your_test_executable
```

Replace \`your_test_executable\` with the actual name of your test executable.
In our case is: ./data-structures_test

## With the ctest command

1. **To run all tests that are in the \`build/test\` folder, use this:
You can also add --verbose flag.**

```bash
GTEST_COLOR=1 ctest --test-dir build/test --output-on-failure -j12
```

2. **To run all test of a structure/iterator:**

```bash
GTEST_COLOR=1 ctest --test-dir build/test --output-on-failure -R Structure -j12
```

Replace \`Structure\` with the the structure/iterator you want to test (e.g. DynamicArray, Queue, Iterator)

3. **To run a specified test suite:**

```bash
GTEST_COLOR=1 ctest --test-dir build/test --output-on-failure -R TestSuite -j12
```

Replace \`TestSuite\` with the test suite (e.g. DynamicArrayCompare)

4. **To run a single test, use the following:**

```bash
GTEST_COLOR=1 ctest --test-dir build/test --output-on-failure -R TestSuite.Method -j12
```

Replace c with the test suite (e.g. QueueMethods) and \`Method\` with the testing method (e.g Contains).

## Through shell script (run.sh)

Shell script builds the project for you and allows you to run the executable or tests without building it manually.
To get started, you need to run the following command in the terminal to make the script executable:

```bash
chmod +x run.sh
```

Now you are able to run the script. There are the features:

1. **To run the project executable:**

```bash
./run.sh run
```

2. **To run all the tests:**

```bash
./run.sh tests
```

3. **To run tests for specific data structure:**

```bash
./run.sh tests Structure
```
Replace \`Structure\` with the available data structure. Otherwise, it will throw an error.

---

# Requirements

- CMake 3.3.0 or higher
- A C++ compiler (e.g., g++, clang++)

---
