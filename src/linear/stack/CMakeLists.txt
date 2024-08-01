file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
add_library(Stack STATIC ${SOURCES})
target_link_libraries(Stack PUBLIC Iterator)
target_include_directories(Stack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
