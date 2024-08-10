file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
add_library(Queue STATIC ${SOURCES})
target_link_libraries(Queue PUBLIC QueueIterator)
target_include_directories(Queue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
