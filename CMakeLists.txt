cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include (utils.cmake)

include(CTest)
enable_testing()
#include_directories(scoup_storage)
#add_executable(demo main.cpp scoup_storage/a.cpp scoup_storage/b.cpp)


#add_executable(spsc_queue_demo spsc_queue_demo.cpp)
#target_link_libraries(spsc_queue_demo PRIVATE pthread)

#add_definitions(-Wno-builtin-macro-redefined)
#add_executable(extern_demo a.cpp src/extern_demo.cpp b.cpp)
#redefine_file_macro(extern_demo)

add_subdirectory(file_demo)

add_subdirectory(log_filter)

add_subdirectory(storage_demo)

add_subdirectory(function_obj_queue)

add_subdirectory(thread_local_demo)

#add_subdirectory(template_demo)

#add_subdirectory(google_benchmark_demo)

#add_subdirectory(static_global_demo)

add_subdirectory(weak_symbol)

add_subdirectory(preprocess_macro_demo)

add_subdirectory(dlopen_demo)

add_subdirectory(inline_demo)

add_subdirectory(eigen_demo)

#add_subdirectory(lcm_demo)
add_subdirectory(yaml_include_demo)

add_subdirectory(cmake_add_custom_command_demo)

add_subdirectory(stl_vector_demo)
add_subdirectory(stl_iterator_adaptor_demo)
add_subdirectory(dynamic_load)
add_subdirectory(json_parser)
add_subdirectory(waitpid_demo)
add_subdirectory(signal_demo)
add_subdirectory(double_buffer_demo)
add_subdirectory(shared_ptr_mult_thread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
