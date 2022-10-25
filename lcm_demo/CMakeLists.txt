include_directories(msgs)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /opt/px_control/)
include_directories(/opt/px_control/include/)
link_directories(/opt/px_control/lib/)
add_executable(lcm_talker talker/talker.cpp)
target_link_libraries(lcm_talker lcm pthread)

add_executable(lcm_listener listener/listener.cpp)
target_link_libraries(lcm_listener lcm pthread)
