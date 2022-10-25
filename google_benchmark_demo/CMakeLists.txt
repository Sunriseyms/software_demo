add_executable(google_benchmark google_benchmark.cpp)
target_link_libraries(google_benchmark PRIVATE benchmark pthread)

#CMAKE_CXX_FLAGS_RELEASE = -O3 -DNDEBUG
add_executable(bench_demo benchmark_demo.cpp)
set_target_properties(bench_demo PROPERTIES CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -g")
