file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
add_library(LinkedList STATIC ${SOURCES})
target_include_directories(LinkedList PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
