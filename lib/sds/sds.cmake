add_library(sds
    STATIC ${PROJECT_SOURCE_DIR}/lib/sds/sds.cpp)

set(SDS_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include/sds
    CACHE INTERNAL "sds: Include Directories" FORCE)