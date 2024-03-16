message(STATUS "Looking for redis dependency")
include(ExternalProject)

ExternalProject_Add(redis-sds
        GIT_REPOSITORY https://github.com/antirez/sds.git
        GIT_TAG 2.0.0
)