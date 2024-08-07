set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE LINEAR_TEST_SOURCES LIST_DIRECTORIES false "linear/*.cpp")
file(GLOB_RECURSE ITERATOR_TEST_SOURCES LIST_DIRECTORIES false "iterators/*.cpp")

set(TEST_SOURCES ${LINEAR_TEST_SOURCES} ${ITERATOR_TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES} main.cpp)

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)
target_include_directories(${BINARY} PUBLIC
    ${PROJECT_SOURCE_DIR}/src/linear/dynamic-array
    ${PROJECT_SOURCE_DIR}/src/linear/stack
    ${PROJECT_SOURCE_DIR}/src/linear/queue
    ${PROJECT_SOURCE_DIR}/src/utils/iterator
    ${PROJECT_SOURCE_DIR}/src/utils/queue-iterator
)


include(GoogleTest)
gtest_discover_tests(${BINARY}
  DISCOVERY_MODE PRE_TEST
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_BINARY_DIR}")

enable_testing()
