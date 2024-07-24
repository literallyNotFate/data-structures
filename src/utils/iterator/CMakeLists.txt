file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
add_library(Iterator STATIC ${SOURCES})
target_include_directories(Iterator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
