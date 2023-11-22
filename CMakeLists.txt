cmake_minimum_required(VERSION 3.15)

project(LINK_THIRD_PARTY)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(third_party)

add_subdirectory(src)