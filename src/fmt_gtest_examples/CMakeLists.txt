


add_executable(test_fmt test_fmt.cc)
target_include_directories(test_fmt PRIVATE
    ../../third_party/fmt/include
)
target_link_libraries(test_fmt fmt)


add_executable(sample1_unittest sample1_unittest.cc sample1.cc)
target_include_directories(sample1_unittest PRIVATE
    ../../third_party/googletest/googletest/include
)

target_link_libraries(sample1_unittest gtest_main)