cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 20)

set(HEADERS${CMAKE_SOURCE_DIR}
/include)

set(TESTS ${CMAKE_SOURCE_DIR}/tests)

set(SRC ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(tests)