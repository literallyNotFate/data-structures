file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
add_library(QueueIterator STATIC ${SOURCES})
target_link_libraries(QueueIterator PUBLIC Queue)
target_include_directories(QueueIterator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
