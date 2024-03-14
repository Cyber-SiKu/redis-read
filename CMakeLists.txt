cmake_minimum_required(VERSION 3.27)
project(redis_read)

set(CMAKE_CXX_STANDARD 14)

include_directories(sds)
add_subdirectory(sds)

add_executable(redis_read main.cpp)
target_link_libraries(redis_read PRIVATE sds)
