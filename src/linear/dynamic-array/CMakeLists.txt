file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
add_library(DynamicArray STATIC ${SOURCES})
target_link_libraries(DynamicArray PUBLIC Iterator)
target_include_directories(DynamicArray PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
