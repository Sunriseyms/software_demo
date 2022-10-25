cmake_minimum_required(VERSION 3.0.0)
project(atomic_test VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(atomic_test main.cpp)
target_link_libraries(atomic_test pthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
