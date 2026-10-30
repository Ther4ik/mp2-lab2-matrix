set(target ${MP2_TESTS})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.c*")

add_executable(${target} ${srcs} ${hdrs})
target_include_directories(${target} PUBLIC "${MP2_GTEST_INCLUDES}" "${MP2_INCLUDES}")
target_link_libraries(${target} gtest ${MP2_LIBRARY})
add_test(${target} ${target})
