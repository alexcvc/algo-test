set(TargetName find_in_vector)

add_executable(${TargetName} main.cpp)
target_link_libraries(${TargetName} fmt)