set(CMAKE_BUILD_TYPE DEBUG)
add_library(node_handle SHARED node_handler.h node_handler.cpp)
target_link_libraries(node_handle boost_system)

add_library(instance instance.cpp instance.h)

add_executable(main main.cpp)
target_link_libraries(main node_handle instance)
