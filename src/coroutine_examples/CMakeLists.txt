add_executable(coroutine1 coroutine1.cpp)
target_include_directories(coroutine1 PRIVATE ../../third_party/fmt/include)
target_link_libraries(coroutine1 fmt)

add_executable(coroutine3 coroutine3.cpp)
target_include_directories(coroutine3 PRIVATE ../../third_party/fmt/include)
target_link_libraries(coroutine3 fmt)

add_executable(coroutine4 coroutine4.cpp)
target_include_directories(coroutine4 PRIVATE ../../third_party/fmt/include)
target_link_libraries(coroutine4 fmt)