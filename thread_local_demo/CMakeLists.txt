add_executable(thread_local_demo main.cpp)

target_link_libraries(thread_local_demo PRIVATE pthread)
