set(TargetName scale_i16)

add_executable(${TargetName} main.cpp)
target_link_libraries(${TargetName} fmt)