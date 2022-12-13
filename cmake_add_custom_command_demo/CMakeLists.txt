#file(GENERATED OUTPUT script_demo.sh INPUT test.sh) 
set(Test "test")
message("xxxxxxxxxxxxxxxxxxxxx:"${CMAKE_CURRENT_LIST_FILE})
add_custom_command(OUTPUT test_out
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test.sh ${Test}
)

add_custom_target(test1 DEPENDS test_out)

add_executable(cmake_demo main.cpp)
add_dependencies(cmake_demo test1)