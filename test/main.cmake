include_directories(
    ${FMT_INCLUDE_DIR}/include
    ${SDS_INCLUDE_DIRS}
)

add_executable(main ${PROJECT_SOURCE_DIR}/test/main.cpp
        ${PROJECT_SOURCE_DIR}/test/sds/sds.cpp
)

target_link_libraries(main
    PUBLIC ${FMT_LIBRARY}
    PUBLIC sds
)

add_dependencies(main sds fmt)
