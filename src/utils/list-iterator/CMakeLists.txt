file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
add_library(ListIterator STATIC ${SOURCES})
target_link_libraries(ListIterator PUBLIC LinkedList)
target_include_directories(ListIterator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
