set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(static_a STATIC static_lib/a.h static_lib/a.cpp)

add_library(math1 math1.h math1.cpp)
add_library(math_demo SHARED math_demo.h math_demo.cpp)
target_link_libraries(math_demo PRIVATE math1 static_a)

add_library(student SHARED class_student.cpp)
target_link_libraries(student PRIVATE
    static_a)
target_include_directories(student PRIVATE ../)
