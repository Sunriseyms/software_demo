add_executable(cgroup_demo main.cpp)
target_link_libraries(cgroup_demo pthread)

install(TARGETS cgroup_demo DESTINATION ${CMAKE_BINARY_DIR}/bin)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/script DESTINATION ${CMAKE_BINARY_DIR})