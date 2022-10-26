add_executable(yaml_include_demo main.cpp yaml_parse.h yaml_parse.cpp)
target_link_libraries(yaml_include_demo yaml-cpp)