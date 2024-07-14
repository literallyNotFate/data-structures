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

## Building the Project

To build the project, follow these steps:

```bash
mkdir build
cd build
cmake ..
make
```

---

## Running the Tests

To run the tests, use the following command:

```bash
./build/your_test_executable
```

Replace \`your_test_executable\` with the actual name of your test executable.

## Or

```bash
GTEST_COLOR=1 ctest --test-dir build/test --output-on-failure -j12
```

---

## Requirements

- CMake 3.3.0 or higher
- A C++ compiler (e.g., g++, clang++)

---
