set(BINARY ${CMAKE_PROJECT_NAME}_test)
set(SOURCES ${TEST_SOURCES})

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
add_executable(${BINARY} ${TEST_SOURCES})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)
target_include_directories(${BINARY} PUBLIC
    ${PROJECT_SOURCE_DIR}/src/linear/dynamic-array
    ${PROJECT_SOURCE_DIR}/src/utils/iterator
)

include(GoogleTest)
gtest_discover_tests(${BINARY}
  DISCOVERY_MODE PRE_TEST
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_BINARY_DIR}")

enable_testing()
