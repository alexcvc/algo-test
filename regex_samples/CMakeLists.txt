set(TargetName regex_samples)

add_executable(${TargetName} main.cpp)
target_link_libraries(${TargetName} fmt)