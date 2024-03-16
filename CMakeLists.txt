cmake_minimum_required(VERSION 3.27)
project(redis_read)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

set(CMAKE_INSTALL_PREFIX ${CMAKE_BUILD_RPATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BUILD_RPATH})

include(${PROJECT_SOURCE_DIR}/third_party/fmt.cmake)

include(${PROJECT_SOURCE_DIR}/lib/sds/sds.cmake)

include(${PROJECT_SOURCE_DIR}/test/main.cmake)
