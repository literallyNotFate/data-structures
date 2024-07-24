add_subdirectory(linear)
add_subdirectory(utils)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *.h *.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
