add_subdirectory(test_lib)

add_executable(dlopen_demo main.cpp)
target_link_libraries(dlopen_demo dl)
