add_executable(cgroup_demo main.cpp)
target_link_libraries(cgroup_demo pthread)

add_executable(mem_demo mem_demo.cpp)
target_link_libraries(mem_demo pthread)

add_executable(mem_event mem_event.cpp)
target_link_libraries(mem_event PUBLIC pthread)

add_executable(cpu_demo cpu_demo.cpp)
target_link_libraries(cpu_demo PUBLIC pthread)

install(TARGETS cgroup_demo DESTINATION ${CMAKE_BINARY_DIR}/bin)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/script DESTINATION ${CMAKE_BINARY_DIR})